

#include "MyProject.h"

/************************************************
本程序仅供学习，引用代码请标明出处
使用教程：https://blog.csdn.net/loop222/article/details/120471390
创建日期：20210925
作    者：loop222 @郑州
************************************************/
/******************************************************************************/
float pid_vel_P, pid_ang_P;//比例变量
float pid_vel_I, pid_ang_D;//积分、微分变量
float integral_vel_prev;//上一次的积分值
float error_vel_prev, error_ang_prev;//上一次的速度、角度误差
float output_vel_ramp;//电压上升速度限幅值
float output_vel_prev;//上一次的速度环输出
unsigned long pid_vel_timestamp, pid_ang_timestamp;//速度、角度环上次进入的系统时间
/******************************************************************************/
void PID_init(void)
{
	pid_vel_P=0.1;  //速度环比例系数
	pid_vel_I=2;    //速度环积分系数
	output_vel_ramp=100;       //output derivative limit [volts/second] 电压上升速度限幅值
	integral_vel_prev=0;//上一次的积分值
	error_vel_prev=0;//上一次的速度误差
	output_vel_prev=0;//上一次的速度环输出
	pid_vel_timestamp=SysTick->VAL;
	
	pid_ang_P=5;//位置环比例系数
	pid_ang_D=0.25;//位置环微分系数
	error_ang_prev=0;//上一次的角度误差
	pid_ang_timestamp=SysTick->VAL;
}
/******************************************************************************/
//just P&I is enough,no need D 
float PID_velocity(float error)
{
	unsigned long now_us;
	float Ts;
	float proportional,integral,output;
	float output_rate;
	
	now_us = SysTick->VAL;
	if(now_us<pid_vel_timestamp)Ts = (float)(pid_vel_timestamp - now_us)/9*1e-6f;
	else
		Ts = (float)(0xFFFFFF - now_us + pid_vel_timestamp)/9*1e-6f;
	pid_vel_timestamp = now_us;
	if(Ts == 0 || Ts > 0.5) Ts = 1e-3f;
	
	// u(s) = (P + I/s )e(s) 只有P和I，没有D
	// Discrete implementations 离散实现
	// proportional part 
	// u_p  = P *e(k)
	proportional = pid_vel_P * error;//比例部分
	// Tustin transform of the integral part
	// u_ik = u_ik_1  + I*Ts*(ek + ek_1)/2 除以2算滤波吧
	integral = integral_vel_prev + pid_vel_I*Ts*0.5*(error + error_vel_prev);//积分部分
	// antiwindup - limit the output
	integral = _constrain(integral, -voltage_limit, voltage_limit);//积分输出限幅
	
	// sum all the components
	output = proportional + integral;
	// antiwindup - limit the output variable
	output = _constrain(output, -voltage_limit, voltage_limit);//PI输出限幅
	
	// limit the acceleration by ramping the output
	output_rate = (output - output_vel_prev)/Ts;//限制PI上升速度
	if(output_rate > output_vel_ramp)output = output_vel_prev + output_vel_ramp*Ts;
	else if(output_rate < -output_vel_ramp)output = output_vel_prev - output_vel_ramp*Ts;
	
	// saving for the next pass 保存变量值以供下次计算
	integral_vel_prev = integral;
	output_vel_prev = output;
	error_vel_prev = error;
	
	return output;
}
/******************************************************************************/
//P&D for angle_PID
float PID_angle(float error)
{
	unsigned long now_us;
	float Ts;
	float proportional,derivative,output;
	//float output_rate;
	
	now_us = SysTick->VAL;
	if(now_us<pid_ang_timestamp)Ts = (float)(pid_ang_timestamp - now_us)/9*1e-6f;
	else
		Ts = (float)(0xFFFFFF - now_us + pid_ang_timestamp)/9*1e-6f;
	pid_ang_timestamp = now_us;
	if(Ts == 0 || Ts > 0.5) Ts = 1e-3f;
	
	// u(s) = (P + I/s + Ds)e(s) 只有P和D，没有I
	// Discrete implementations 离散实现
	// proportional part 比例部分
	// u_p  = P *e(k)
	proportional = pid_ang_P * error;
	// u_dk = D(ek - ek_1)/Ts 微分部分
	derivative = pid_ang_D*(error - error_ang_prev)/Ts;
	
	output = proportional + derivative;
	output = _constrain(output, -velocity_limit, velocity_limit);//输出限幅
	
	// limit the acceleration by ramping the output
//	output_rate = (output - output_ang_prev)/Ts;
//	if(output_rate > output_ang_ramp)output = output_ang_prev + output_ang_ramp*Ts;
//	else if(output_rate < -output_ang_ramp)output = output_ang_prev - output_ang_ramp*Ts;
	
	// saving for the next pass 
//	output_ang_prev = output;
	error_ang_prev = error;//保存误差以供下次计算
	
	return output;
}
/******************************************************************************/
/******************************************************************************/

