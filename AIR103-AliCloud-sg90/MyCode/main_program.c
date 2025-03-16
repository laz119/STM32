#include "main_program.h"
#include <stdio.h>
#include "time_handle.h"
#include "led.h"


/*
*************************************
�궨��
*************************************
*/

/*
*************************************
��������
*************************************
*/
extern uint16_t index_led;
/*
*************************************
��������
*************************************
*/

/*
*************************************
��������
*************************************
*/
uint8_t led_status =0;
/*
*************************************
��������
*************************************
*/

/**
  * @brief          ��ʼ������,�൱��Arduino��setup()����,ֻ�ڳ�ʼ��ʱ��ִ��һ��
  * @param[in]      none
  * @retval         none
  */
void user_init_program(void)
{
  time_slot_start();
}
/**
  * @brief          ��ʼ������,�൱��Arduino��loop()����,һֱִ�иú���
  * @param[in]      none
  * @retval         none
  */
void user_main_program(void)
{
  if(index_led==1)
  {
    led_status = !led_status;
    set_led(led_status);
    printf("hello,world\r\n");
    index_led=0;
  }
}

