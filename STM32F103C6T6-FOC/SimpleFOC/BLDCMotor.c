
#include "MyProject.h"


/************************************************
main中调用的接口函数都在当前文件中
=================================================
本程序仅供学习，引用代码请标明出处
使用教程：https://blog.csdn.net/loop222/article/details/120471390
创建日期：20210925
作    者：loop222 @郑州
************************************************/
/******************************************************************************/
extern float target;
/******************************************************************************/
long sensor_direction;//传感器方向
float voltage_power_supply;//电源电压
float voltage_limit;//电压矢量最大值
float voltage_sensor_align;//电压传感器偏移量
int  pole_pairs;//极对数
unsigned long open_loop_timestamp;//开环计时变量
float velocity_limit;//速度上限
/******************************************************************************/
int alignSensor(void);
float velocityOpenloop(float target_velocity);
float angleOpenloop(float target_angle);
/******************************************************************************/
void Motor_init(void)
{
	printf("MOT: Init\r\n");
	
//	new_voltage_limit = current_limit * phase_resistance;
//	voltage_limit = new_voltage_limit < voltage_limit ? new_voltage_limit : voltage_limit;
	if(voltage_sensor_align > voltage_limit) voltage_sensor_align = voltage_limit;//限幅，传感器对齐电压不要超过电压矢量最大值
	
	pole_pairs=7;//配置极对数为7
	sensor_direction=UNKNOWN;//配置传感器方向为未知
	
	M1_Enable;//使能电机驱动芯片
	printf("MOT: Enable driver.\r\n");
}
/******************************************************************************/
void Motor_initFOC(void)
{
	alignSensor();    //检测零点偏移量和极对数
	
	//added the shaft_angle update 增加了shaft_angle更新
	angle_prev=getAngle();  //必须调用一次，保存当前角度
	delay_ms(5);
	shaft_velocity = shaftVelocity();  //必须调用一次，进入主循环后速度为0
	delay_ms(5);
	shaft_angle = shaftAngle();// shaft angle 计算转子角度
	if(controller==Type_angle)target=shaft_angle;//如果是角度模式，以当前的角度为目标角度，进入主循环后电机静止
	
	delay_ms(200);
}
/******************************************************************************/
int alignSensor(void)
{
	long i;
	float angle;
	float mid_angle,end_angle;
	float moved;
	
	printf("MOT: Align sensor.\r\n");
	
	// find natural direction 找到旋转方向对应的位置传感器数据变化方向
	// move one electrical revolution forward 旋转一个完整360°的电角度
	for(i=0; i<=500; i++)
	{
		angle = _3PI_2 + _2PI * i / 500.0;//_3PI_2是因为setPhaseVoltage里会加_PI_2
		setPhaseVoltage(voltage_sensor_align, 0,  angle);//设置相电压
		delay_ms(2);
	}
	mid_angle=getAngle();//记录此时角度值
	
	for(i=500; i>=0; i--) //再转回去
	{
		angle = _3PI_2 + _2PI * i / 500.0 ;
		setPhaseVoltage(voltage_sensor_align, 0,  angle);
		delay_ms(2);
	}
	end_angle=getAngle();//记录此时角度值
	setPhaseVoltage(0, 0, 0);//关闭PWM
	delay_ms(200);
	
	printf("mid_angle=%.4f\r\n",mid_angle);
	printf("end_angle=%.4f\r\n",end_angle);
	
	moved =  fabs(mid_angle - end_angle);//计算角度差
	if((mid_angle == end_angle)||(moved < 0.02))  //相等或者几乎没有动
	{
		printf("MOT: Failed to notice movement loop222.\r\n");
		M1_Disable;    //电机检测不正常，关闭驱动
		return 0;
	}
	else if(mid_angle < end_angle)
	{
		printf("MOT: sensor_direction==CCW\r\n");
		sensor_direction=CCW;//逆时针
	}
	else
	{
		printf("MOT: sensor_direction==CW\r\n");
		sensor_direction=CW;//顺时针
	}
	
	
	printf("MOT: PP check: ");    //计算Pole_Pairs极对数
	if( fabs(moved*pole_pairs - _2PI) > 0.5 )  // 0.5 is arbitrary number it can be lower or higher! 0.5是一个任意数字，它可以更低或更高!
	{
//		printf("fail - estimated pp:");
//		pole_pairs=_2PI/moved+0.5;     //浮点数转整形，四舍五入
		pole_pairs=7;
		printf("%d\r\n",pole_pairs);
  }
	else
		printf("OK!\r\n");
	
	
	setPhaseVoltage(voltage_sensor_align, 0,  _3PI_2);  //设置电压矢量指向电角度0
	delay_ms(700);
	zero_electric_angle = _normalizeAngle(_electricalAngle(sensor_direction*getAngle(), pole_pairs));//传感器0°相对电角度0°的偏移度数
	delay_ms(20);
	printf("MOT: Zero elec. angle:");
	printf("%.4f\r\n",zero_electric_angle);
	
	setPhaseVoltage(0, 0, 0);//关闭PWM
	delay_ms(200);
	
	return 1;
}
/******************************************************************************/
void loopFOC(void)
{
	if( controller==Type_angle_openloop || controller==Type_velocity_openloop ) return;//开环部分不在这里
	
	shaft_angle = shaftAngle();// 再读取一次转子角度
	electrical_angle = electricalAngle();// electrical angle - need shaftAngle to be called first 计算电角度
	
	switch(torque_controller)
	{
		case Type_voltage:  // no need to do anything really
			break;
		case Type_dc_current:
			break;
		case Type_foc_current:
			break;
		default:
			printf("MOT: no torque control selected!");
			break;
	}
	// set the phase voltage - FOC heart function :)根据电压矢量计算PWM比较值
  setPhaseVoltage(voltage.q, voltage.d, electrical_angle);
}
/******************************************************************************/
void move(float new_target)
{
	shaft_velocity = shaftVelocity();//读取转速
	
	switch(controller)
	{
		case Type_torque://扭矩模式
			if(torque_controller==Type_voltage)voltage.q = new_target;  // if voltage torque control 如果扭矩通过电压来给定
		  else
				current_sp = new_target; // if current/foc_current torque control
			break;
		case Type_angle://角度闭环模式
			// angle set point 设置角度目标值
      shaft_angle_sp = new_target;
      // calculate velocity set point 角度误差PID
      shaft_velocity_sp = PID_angle( shaft_angle_sp - shaft_angle );
      // calculate the torque command 速度误差PID
      current_sp = PID_velocity(shaft_velocity_sp - shaft_velocity); // if voltage torque control
      // if torque controlled through voltage  如果扭矩通过电压来给定
      if(torque_controller == Type_voltage)
			{
				voltage.q = current_sp;
        voltage.d = 0;
      }
			break;
		case Type_velocity://速度闭环模式
			// velocity set point 设置速度目标值
      shaft_velocity_sp = new_target;
      // calculate the torque command 速度误差PID
      current_sp = PID_velocity(shaft_velocity_sp - shaft_velocity); // if current/foc_current torque control
      // if torque controlled through voltage control 如果扭矩通过电压来给定
      if(torque_controller == Type_voltage)
			{
        voltage.q = current_sp;  // use voltage if phase-resistance not provided
        voltage.d = 0;
      }
			break;
		case Type_velocity_openloop://速度开环模式
			// velocity control in open loop
      shaft_velocity_sp = new_target;
      voltage.q = velocityOpenloop(shaft_velocity_sp); // returns the voltage that is set to the motor
      voltage.d = 0;
			break;
		case Type_angle_openloop://角度开环模式
			// angle control in open loop
      shaft_angle_sp = new_target;
      voltage.q = angleOpenloop(shaft_angle_sp); // returns the voltage that is set to the motor
      voltage.d = 0;
			break;
	}
}
/********************************根据电压矢量计算PWM比较值**********************************************/
void setPhaseVoltage(float Uq, float Ud, float angle_el)
{
	float Uout;
	uint32_t sector;//扇区号
	float T0,T1,T2;
	float Ta,Tb,Tc;
	
	if(Ud) // only if Ud and Uq set 求反正切要保证分母不为零
	{// _sqrt is an approx of sqrt (3-4% error) _sqrt是sqrt的近似值(误差为3-4%)
		Uout = _sqrt(Ud*Ud + Uq*Uq) / voltage_power_supply;
		// angle normalisation in between 0 and 2pi 角度归一化在0到2pi之间
		// only necessary if using _sin and _cos - approximation functions 只有在使用_sin和_cos近似函数时才有必要
		angle_el = _normalizeAngle(angle_el + atan2(Uq, Ud));
	}
	else
		{// only Uq available - no need for atan2 and sqrt也就是Ud为0
		Uout = Uq / voltage_power_supply;
		// angle normalisation in between 0 and 2pi 角度归一化在0到2pi之间
		// only necessary if using _sin and _cos - approximation functions 只有在使用_sin和_cos近似函数时才有必要
		angle_el = _normalizeAngle(angle_el + _PI_2);
	}
	if(Uout> 0.577)Uout= 0.577;
	if(Uout<-0.577)Uout=-0.577;
	
	sector = (angle_el / _PI_3) + 1;
	T1 = _SQRT3*_sin(sector*_PI_3 - angle_el) * Uout;//跟3*sin(扇区号*pi/3-angle_el)*Uout
	T2 = _SQRT3*_sin(angle_el - (sector-1.0)*_PI_3) * Uout;//跟3*sin(angle_el-(扇区号-1.0)*pi/3)*Uout
	T0 = 1 - T1 - T2;
	
	// calculate the duty cycles(times)计算比较值
	switch(sector)
	{
		case 1:
			Ta = T1 + T2 + T0/2;
			Tb = T2 + T0/2;
			Tc = T0/2;
			break;
		case 2:
			Ta = T1 +  T0/2;
			Tb = T1 + T2 + T0/2;
			Tc = T0/2;
			break;
		case 3:
			Ta = T0/2;
			Tb = T1 + T2 + T0/2;
			Tc = T2 + T0/2;
			break;
		case 4:
			Ta = T0/2;
			Tb = T1+ T0/2;
			Tc = T1 + T2 + T0/2;
			break;
		case 5:
			Ta = T2 + T0/2;
			Tb = T0/2;
			Tc = T1 + T2 + T0/2;
			break;
		case 6:
			Ta = T1 + T2 + T0/2;
			Tb = T0/2;
			Tc = T1 + T0/2;
			break;
		default:  // possible error state
			Ta = 0;
			Tb = 0;
			Tc = 0;
	}
	
	TIM_SetCompare1(TIM2,Ta*PWM_Period);
	TIM_SetCompare2(TIM2,Tb*PWM_Period);
	TIM_SetCompare3(TIM2,Tc*PWM_Period);
}
/******************************************************************************/
float velocityOpenloop(float target_velocity)
{
	unsigned long now_us;
	float Ts,Uq;
	
	now_us = SysTick->VAL; //_micros();
	if(now_us<open_loop_timestamp)Ts = (float)(open_loop_timestamp - now_us)/9*1e-6;
	else
		Ts = (float)(0xFFFFFF - now_us + open_loop_timestamp)/9*1e-6;
	open_loop_timestamp=now_us;  //save timestamp for next call
  // quick fix for strange cases (micros overflow)
  if(Ts == 0 || Ts > 0.5) Ts = 1e-3; 
	
	// calculate the necessary angle to achieve target velocity
  shaft_angle = _normalizeAngle(shaft_angle + target_velocity*Ts); 
	
	Uq = voltage_limit;
	// set the maximal allowed voltage (voltage_limit) with the necessary angle
  setPhaseVoltage(Uq,  0, _electricalAngle(shaft_angle, pole_pairs));
	
	return Uq;
}
/******************************************************************************/
float angleOpenloop(float target_angle)
{
	unsigned long now_us;
	float Ts,Uq;
	
	now_us = SysTick->VAL; //_micros();
	if(now_us<open_loop_timestamp)Ts = (float)(open_loop_timestamp - now_us)/9*1e-6;
	else
		Ts = (float)(0xFFFFFF - now_us + open_loop_timestamp)/9*1e-6;
  open_loop_timestamp = now_us;  //save timestamp for next call
  // quick fix for strange cases (micros overflow)
  if(Ts == 0 || Ts > 0.5) Ts = 1e-3; 
	
	// calculate the necessary angle to move from current position towards target angle
  // with maximal velocity (velocity_limit)
  if(fabs( target_angle - shaft_angle ) > velocity_limit*Ts)
	{
    shaft_angle += _sign(target_angle - shaft_angle) * velocity_limit * Ts;
    //shaft_velocity = velocity_limit;
  }
	else
	{
    shaft_angle = target_angle;
    //shaft_velocity = 0;
  }
	
	Uq = voltage_limit;
	// set the maximal allowed voltage (voltage_limit) with the necessary angle
	setPhaseVoltage(Uq,  0, _electricalAngle(shaft_angle, pole_pairs));
	
  return Uq;
}
/******************************************************************************/



