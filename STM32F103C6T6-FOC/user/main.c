
#include "stm32f10x.h"
#include <stdlib.h>
#include "MyProject.h"


/************************************************
SimpleMotor开发板
闭环控制  演示
1、力矩模式
2、速度模式
3、位置模式
=================================================
本程序仅供学习，引用代码请标明出处
使用教程：https://blog.csdn.net/loop222/article/details/120471390
创建日期：20210925
作    者：loop222 @郑州
************************************************/
/******************************************************************************/
#define LED_blink    GPIOC->ODR^=(1<<13)
/******************************************************************************/
float target,targetA;//目标值

int cflag=0;//判断是否进入commander_run循环

extern unsigned short USART_RX_STA;
/******************************************************************************/
void commander_run(void);
/******************************************************************************/
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);//使能GPIOA,GPIOB,GPIOC,AFIO;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;         //PC13是LED
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //速度
	GPIO_Init(GPIOC, &GPIO_InitStructure);             //对选中管脚初始化
	GPIO_SetBits(GPIOC,GPIO_Pin_13);                   //上电点亮LED
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          //PB9是motor1的使能
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);                  //低电平解除,Motor_init()中使能
}
/******************************************************************************/
int main(void)
{
	unsigned int count_i=0;
	
	GPIO_Config();//初始化LED口PC13和电机使能口PB9
	uart_init(115200);//初始化串口1的PA9和PA10口，波特率为115200
#if M1_AS5600
	I2C_Init_();               //初始化AS5600的IIC接口PB6和PB7
	printf("AS5600\r\n");
#elif M1_TLE5012B
	SPI2_Init_();              //初始化TLE5012B
	printf("TLE5012B\r\n");
#endif
	TIM2_PWM_Init();					//初始化定时器2的PA0，PA1，PA2
	TIM3_1ms_Init();           //初始化定时器3中断1ms
	
	delay_ms(1000);            //Wait for the system to stabilize
	MagneticSensor_Init();     //读取一次AS5600 or TLE5012B数据
	
	voltage_power_supply=12;   //电源电压，单位V
	voltage_limit=3;           //V，最大值需小于12/1.732=6.9，用于电压矢量的限幅
	velocity_limit=20;         //rad/s angleOpenloop() and PID_angle() use it 速度上限
	voltage_sensor_align=1;    //V     alignSensor() and driverAlign() use it，大功率电机0.5-1，小功率电机2-3 ，用于一开始开环自检
	torque_controller=Type_voltage;  //转矩控制模式，当前只有电压模式
	controller=Type_angle;  //角度Type_angle; //Type_torque;    //Type_velocity速度
	target=1;//目标值为0
	
	Motor_init();//电机参数初始化和驱动芯片使能
	Motor_initFOC();//初始化FOC相关操作
	PID_init();//初始化PID参数
  printf("Motor ready.\r\n");
	
	systick_CountMode();   //不能再调用delay_us()和delay_ms()函数
	
	while(1)
	{
		count_i++;
		
		if(time1_cntr>=200)  //200ms
		{
			time1_cntr=0;
			LED_blink;//LED取反
			
//			if(cflag==2){
//			printf("Motor 22222ready.\r\n");
//				printf("Anglexxxxxxx = %.1f\r\n", getAngle()*180/_PI);
//			if(getAngle()*180/_PI<=target*(-1)+1){
//				target=0;
//				printf("Motor 33333ready.\r\n");
//				cflag=0;
//			}
//			}
			
		}
		if(time2_cntr>=2000) //2000ms
		{
			time2_cntr=0;
			printf("velocity=%.1fr/min,Angle = %.1f\r\n", \
				shaft_velocity*60/_2PI,getAngle()*180/_PI);//打印转速 单位r/min 角度 单位°
			count_i=0;
		}
		move(target);//计算所需电压矢量的大小
		loopFOC();//根据电压矢量生成PWM
		commander_run();//处理串口接收到的命令
		
		if(cflag==1){
			cflag=2;
			printf("Motor 11111ready.\r\n");
			printf("target = %.1f\r\n", target);
		}
		if(cflag==2){
			printf("Motor 22222ready.\r\n");
			printf("Anglexxxxxxx = %.1f\r\n", getAngle()*180/_PI);
			if((getAngle()*180/_PI-1)<=-target){
//				printf("Angleyyyyyyy = %.1f\r\n", target);
				target=0;
				printf("Motor 33333ready.\r\n");
				cflag=0;
			}
			}
		
	}

}
/******************************************************************************/
void commander_run(void)
{
	
	if((USART_RX_STA&0x8000)!=0)
	{
		printf("balabala");
		switch(USART_RX_BUF[0])
		{ 
			case 'H': //测试指令
				printf("Hello World!\r\n");
				break;
			case 'T':   //T6.28 目标值
				target=atof((const char *)(USART_RX_BUF+1));
				if(controller == Type_velocity)	target = target*_2PI/60;//如果是转速模式就将目标值转换为r/min
				if(controller == Type_angle)	target = target*_PI/180;//如果是角度模式就将目标值转换为°
				printf("RX=%.4f\r\n", target);
				break;
			case 'D':   //失能电机驱动芯片
				M1_Disable;
				printf("OK!\r\n");
				break;
			case 'E':   //使能电机驱动芯片
				M1_Enable;
				printf("OK!\r\n");
				break;
			case 'a':   //配置为角度模式
				controller=Type_angle;  //角度Type_angle; //Type_torque;    //Type_velocity
				target = getAngle();
				printf("OK!\r\n");
				break;
			case 't':   //配置为扭矩模式
				controller=Type_torque;  //角度Type_angle; //Type_torque;    //Type_velocity
				target = 0;
				printf("OK!\r\n");
				break;
			case 'v':   //配置为速度模式
				controller=Type_velocity;  //角度Type_angle; //Type_torque;    //Type_velocity
				target = 0;
				printf("OK!\r\n");
				break;
			
				case 'C':   //T6.28 目标值
				target=atof((const char *)(USART_RX_BUF+1));
				target = target*360;
				targetA = target;
//				target = 360*target*_PI/180;//如果是角度模式就将目标值转换为°
				cflag=1;
				printf("RX=%.4f\r\n", target);
				break;
		}
		USART_RX_STA=0;
	}

}
/******************************************************************************/



