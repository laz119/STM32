#include "uart_printf.h"
#include <stdio.h>
#include "usart.h"



/////////////////////////
/////HAL��
/////////////////////////

//#include <stdarg.h>
//#define USART3_SEND_LEN  300

//void USART3_printf (char *fmt, ...) 
//{ 
//	char buffer[USART3_SEND_LEN+1];  // CMD_BUFFER_LEN3��?����??o?����?�㨦 
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



/////�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
//int fputc(int ch,FILE *f)
//{
// 
////������ѯ��ʽ����1�ֽ����ݣ���ʱʱ������Ϊ���޵ȴ�
// 
//HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,HAL_MAX_DELAY);
// 
//return ch;
// 
//}
// 
/////�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
//int fgetc(FILE *f)
// 
//{
// 
//uint8_t ch;
// 
//// ������ѯ��ʽ���� 1�ֽ����ݣ���ʱʱ������Ϊ���޵ȴ�
// 
//HAL_UART_Receive( &huart1,(uint8_t*)&ch,1, HAL_MAX_DELAY );
// 
//return ch;
// 
//}
////�����ض���





//////////////////////////////////////////
//��׼��
//////////////////////////////////////////

/////�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
//int fputc(int ch, FILE *f)
//{
//		/* ����һ���ֽ����ݵ����� */
//		USART_SendData(USART3, (uint8_t) ch);
//		
//		/* �ȴ�������� */
//		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);		
//	
//		return (ch);
//}
// 
/////�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
//int fgetc(FILE *f)
//{
//		/* �ȴ������������� */
//		while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
// 
//		return (int)USART_ReceiveData(USART3);
//}
