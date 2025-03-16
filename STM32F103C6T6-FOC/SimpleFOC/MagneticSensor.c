

#include "MyProject.h"


/************************************************
本程序仅供学习，引用代码请标明出处
使用教程：https://blog.csdn.net/loop222/article/details/120471390
创建日期：20210925
作    者：loop222 @郑州
************************************************/
/******************************************************************************/
long  cpr;//位置传感器满量程
float full_rotation_offset;//全旋转偏移量
long  angle_data_prev;//上一时刻读取到的编码器值
unsigned long velocity_calc_timestamp;//用于速度计算的上一时刻时间
float angle_prev;//上一时刻的角度值
/******************************************************************************/

/******************************************************************************/
#define  AS5600_Address  0x36
#define  RAW_Angle_Hi    0x0C   //V2.1.1 bugfix
//#define  RAW_Angle_Lo    0x0D
#define  AS5600_CPR      4096
/******************************************************************************/
unsigned short I2C_getRawCount(I2C_TypeDef* I2Cx)
{
	uint32_t Timeout;
	unsigned short temp;
	unsigned char dh,dl;	
	
	Timeout = 0xFFFF;
	/* Send START condition */
	I2Cx->CR1 |= 0x0100;//CR1_START_Set;
	/* Wait until SB flag is set: EV5 */
	while ((I2Cx->SR1&0x0001) != 0x0001)
	{
		if (Timeout-- == 0)return 0;
	}
	/* Send the slave address, Reset the address bit0 for write*/
	I2Cx->DR = AS5600_Address<<1;
	Timeout = 0xFFFF;
	/* Wait until ADDR is set: EV6 */
	while ((I2Cx->SR1 &0x0002) != 0x0002)
	{
		if (Timeout-- == 0)return 0;
	}
	/* Clear ADDR flag by reading SR2 register */
	temp = I2Cx->SR2;
	/* Write the first data in DR register (EV8_1) */
	I2Cx->DR = RAW_Angle_Hi;
	/* EV8_2: Wait until BTF is set before programming the STOP */
	while ((I2Cx->SR1 & 0x00004) != 0x000004);
	
	/////////////////////////////////////////////////////////////////////////
	/* Set POS bit */
	I2Cx->CR1 |= 0x0800;//CR1_POS_Set;
	Timeout = 0xFFFF;
	/* Send START condition */
	I2Cx->CR1 |= 0x0100;//CR1_START_Set;
	/* Wait until SB flag is set: EV5 */
	while ((I2Cx->SR1&0x0001) != 0x0001)
	{
		if (Timeout-- == 0)return 0;
	}
	Timeout = 0xFFFF;
	/* Send slave address */
	I2Cx->DR = (AS5600_Address<<1)+1;

	/* Wait until ADDR is set: EV6 */
	while ((I2Cx->SR1&0x0002) != 0x0002)
	{
		if (Timeout-- == 0)return 0;
	}
	/* EV6_1: The acknowledge disable should be done just after EV6,
	that is after ADDR is cleared, so disable all active IRQs around ADDR clearing and 
	ACK clearing */
	__disable_irq();
	/* Clear ADDR by reading SR2 register  */
	temp = I2Cx->SR2;
	/* Clear ACK */
	I2Cx->CR1 &= 0xFBFF;//CR1_ACK_Reset;
	/*Re-enable IRQs */
	__enable_irq();
	/* Wait until BTF is set */
	while ((I2Cx->SR1 & 0x00004) != 0x000004);
	/* Disable IRQs around STOP programming and data reading because of the limitation ?*/
	__disable_irq();
	/* Program the STOP */
	I2C_GenerateSTOP(I2Cx, ENABLE);
	/* Read first data */
	dh = I2Cx->DR;
	/* Re-enable IRQs */
	__enable_irq();
	/**/
	/* Read second data */
	dl = I2Cx->DR;
	/* Make sure that the STOP bit is cleared by Hardware before CR1 write access */
	while ((I2Cx->CR1&0x200) == 0x200);
	/* Enable Acknowledgement to be ready for another reception */
	I2Cx->CR1  |= 0x0400;//CR1_ACK_Set;
	/* Clear POS bit */
	I2Cx->CR1  &= 0xF7FF;//CR1_POS_Reset;
	
	temp++;  //useless,otherwise warning
	return ((dh<<8)+dl);
}
/******************************************************************************/



/******************************************************************************/
//TLE5012B
#define READ_ANGLE_VALUE  0x8020
#define TLE5012B_CPR      32768
/******************************************************************************/
#define SPI2_CS1_L  GPIO_ResetBits(GPIOB, GPIO_Pin_8)      //CS1_L
#define SPI2_CS1_H  GPIO_SetBits(GPIOB, GPIO_Pin_8)        //CS1_H

#define SPI2_TX_OFF {GPIOB->CRH&=0x0FFFFFFF;GPIOB->CRH|=0x40000000;}  //把PB15(MOSI)配置为浮空输入模式
#define SPI2_TX_ON  {GPIOB->CRH&=0x0FFFFFFF;GPIOB->CRH|=0xB0000000;}  //把PB15(MOSI)复用推挽输出(50MHz)
/******************************************************************************/
unsigned short SPIx_ReadWriteByte(unsigned short byte)
{
	unsigned short retry = 0;
	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
	{
		if(++retry>200)return 0;
	}
	SPI_I2S_SendData(SPI2, byte);
	retry = 0;
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) 
	{
		if(++retry>200)return 0;
	}
	return SPI_I2S_ReceiveData(SPI2);
}
/******************************************************************************/
unsigned short ReadTLE5012B_1(unsigned short Comm)
{
	unsigned short u16Data;
	
	SPI2_CS1_L;
	SPIx_ReadWriteByte(Comm);
	SPI2_TX_OFF;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();  //Twr_delay=130ns min
	u16Data = SPIx_ReadWriteByte(0xffff);
	
	SPI2_CS1_H;
	SPI2_TX_ON;
	return(u16Data);
}
/******************************************************************************/
//#endif

/******************************************************************************/
void MagneticSensor_Init(void)
{
#if M1_AS5600
	cpr=AS5600_CPR;
	angle_data_prev = I2C_getRawCount(I2C1);  
#elif M1_TLE5012B
	cpr=TLE5012B_CPR;
	angle_data_prev = ReadTLE5012B_1(READ_ANGLE_VALUE)&0x7FFF;
#endif
	
	full_rotation_offset = 0;
	velocity_calc_timestamp=0;
}
/******************************************************************************/
float getAngle(void)
{
	float angle_data,d_angle;
	
#if M1_AS5600
	angle_data = I2C_getRawCount(I2C1);
#elif M1_TLE5012B
	angle_data = ReadTLE5012B_1(READ_ANGLE_VALUE)&0x7FFF;
#endif
	
	// tracking the number of rotations 跟踪旋转次数
	// in order to expand angle range form [0,2PI] to basically infinity 以便将角度范围从[0,2 pi]扩展到几乎无穷大
	d_angle = angle_data - angle_data_prev;//计算角度变化量
	// if overflow happened track it as full rotation 如果溢出发生，跟踪它为完全旋转
	//fabs()用于求双精度浮点数的绝对值
	if(fabs(d_angle) > (0.8*cpr) ) full_rotation_offset += d_angle > 0 ? -_2PI : _2PI; //
	// save the current angle value for the next steps 保存当前的角度值以供下一步使用
	// in order to know if overflow happened 以便了解是否发生溢出
	angle_data_prev = angle_data;
	// return the full angle 返回全角度
	// (number of full rotations)*2PI + current sensor angle (全旋转次数)*2PI +电流传感器角度
	// cpr为编码器满量程（4096）
	return  (full_rotation_offset + ( angle_data / (float)cpr) * _2PI) ;
}
/******************************************************************************/
// Shaft velocity calculation 计算磁编码速度
float getVelocity(void)
{
	unsigned long now_us;
	float Ts, angle_c, vel;

	// calculate sample time 计算间隔时间
	now_us = SysTick->VAL; //_micros();
	if(now_us<velocity_calc_timestamp)Ts = (float)(velocity_calc_timestamp - now_us)/9*1e-6;//9Mhz/9=1Mhz，单位s
	else
		Ts = (float)(0xFFFFFF - now_us + velocity_calc_timestamp)/9*1e-6;
	// quick fix for strange cases (micros overflow) 快速修复奇怪的情况(micros溢出)
	if(Ts == 0 || Ts > 0.5) Ts = 1e-3;

	// current angle 当前角度
	angle_c = getAngle();
	// velocity calculation 速度计算
	vel = (angle_c - angle_prev)/Ts;

	// save variables for future pass 保存角度和时刻
	angle_prev = angle_c;
	velocity_calc_timestamp = now_us;
	return vel;
}
/******************************************************************************/



