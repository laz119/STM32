#include "uart_printf.h"
#include <stdio.h>
#include "usart.h"



/////////////////////////
/////HAL库
/////////////////////////

//#include <stdarg.h>
//#define USART3_SEND_LEN  300

//void USART3_printf (char *fmt, ...) 
//{ 
//	char buffer[USART3_SEND_LEN+1];  // CMD_BUFFER_LEN3¤?è×??o?¨ò?°é 
//	int i = 0; 

//	va_list arg_ptr; 
//	va_start(arg_ptr, fmt);   
//	vsnprintf(buffer, USART3_SEND_LEN+1, fmt, arg_ptr); 
//	while ((i < USART3_SEND_LEN) && buffer[i]) 
//	{ 
//					USART_SendData(USART3, (u8) buffer[i++]); 
//	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);  
//	} 
//	va_end(arg_ptr); 
//}



/////重定向c库函数printf到串口，重定向后可使用printf函数
//int fputc(int ch,FILE *f)
//{
// 
////采用轮询方式发送1字节数据，超时时间设置为无限等待
// 
//HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,HAL_MAX_DELAY);
// 
//return ch;
// 
//}
// 
/////重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
//int fgetc(FILE *f)
// 
//{
// 
//uint8_t ch;
// 
//// 采用轮询方式接收 1字节数据，超时时间设置为无限等待
// 
//HAL_UART_Receive( &huart1,(uint8_t*)&ch,1, HAL_MAX_DELAY );
// 
//return ch;
// 
//}
////串口重定向





//////////////////////////////////////////
//标准库
//////////////////////////////////////////

/////重定向c库函数printf到串口，重定向后可使用printf函数
//int fputc(int ch, FILE *f)
//{
//		/* 发送一个字节数据到串口 */
//		USART_SendData(USART3, (uint8_t) ch);
//		
//		/* 等待发送完毕 */
//		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);		
//	
//		return (ch);
//}
// 
/////重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
//int fgetc(FILE *f)
//{
//		/* 等待串口输入数据 */
//		while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
// 
//		return (int)USART_ReceiveData(USART3);
//}
