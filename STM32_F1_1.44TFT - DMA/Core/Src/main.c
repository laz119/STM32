/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "oledfont.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

   float t=0;	
//	 int ChooseShow = 1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int fputc(int ch, FILE *f);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


//LCD显示内容
void LCD_Show(){
	
	int ChooseShow = 9;//选择显示内容
	
	if(ChooseShow == 1){
		LCD_ShowChinese(0,0,"中子",RED,WHITE,24,0);
		LCD_ShowString(24,30,"LCD_W:",RED,WHITE,16,0);
		LCD_ShowIntNum(72,30,LCD_W,3,RED,WHITE,16);
		LCD_ShowString(24,50,"LCD_H:",RED,WHITE,16,0);
		LCD_ShowIntNum(72,50,LCD_H,3,RED,WHITE,16);
		LCD_ShowFloatNum1(20,80,t,4,RED,WHITE,16);
		t+=0.11;
    LCD_ShowPicture(80,70,40,40,gImage_1);
	}
	
	if(ChooseShow == 2){
		LCD_Fill(0,0,LCD_W,LCD_H,RED);
		LCD_Fill(0,0,LCD_W,LCD_H,GREEN);
		LCD_Fill(0,0,LCD_W,LCD_H,BLUE);
	}//三色刷屏
	
	if(ChooseShow == 3){
		LCD_Fill_DMA(0,0,LCD_W,LCD_H,RED);
		LCD_Fill_DMA(0,0,LCD_W,LCD_H,GREEN);
		LCD_Fill_DMA(0,0,LCD_W,LCD_H,BLUE);
	}//三色刷屏——DMA
	
	if(ChooseShow == 4){
		LCD_Fill(0,0,LCD_W,LCD_H,WHITE);	
		LCD_ShowPicture(0,0,128,128,gImage_2);
	}//单色刷屏
	
	if(ChooseShow == 5){
//		LCD_Fill_DMA(0,0,LCD_W,LCD_H,WHITE);	
		LCD_ShowPicture_DMA(0,0,128,128,gImage_2);
	}
	
	if(ChooseShow == 6){
		LCD_Fill_DMA_2(0,0,LCD_W,LCD_H,WHITE);
		HAL_Delay(1000);
		DispPic(0,0,128,128,gImage_2);
		HAL_Delay(1000);
	}	//图片《-》白屏
	
	if(ChooseShow == 7){
		LCD_Fill_DMA_2(0,0,LCD_W,LCD_H,RED);
		HAL_Delay(0);
		LCD_Fill_DMA_2(0,0,LCD_W,LCD_H,GREEN);
		HAL_Delay(0);
		LCD_Fill_DMA_2(0,0,LCD_W,LCD_H,BLUE);
		HAL_Delay(0);
	}	//三色刷屏——DMA
	
	if(ChooseShow == 8){
		
//		DispPic(28,0,101,8,taikongren_1);
		DispPic(32,48,63,32,taikongren_1);
		DispPic(32,48,63,32,taikongren_2);
		DispPic(32,48,63,32,taikongren_3);
		DispPic(32,48,63,32,taikongren_4);
		DispPic(32,48,63,32,taikongren_5);
		DispPic(32,48,63,32,taikongren_6);
		DispPic(32,48,63,32,taikongren_7);
		DispPic(32,48,63,32,taikongren_8);
		DispPic(32,48,63,32,taikongren_9);
		DispPic(32,48,63,32,taikongren_10);
//		HAL_Delay(1000);
	}	
	
		if(ChooseShow == 9){
		
		LCD_ShowPicture_x2(32,48,63,32,taikongren_1);
		LCD_ShowPicture_x2(32,48,63,32,taikongren_2);
		LCD_ShowPicture_x2(32,48,63,32,taikongren_3);
		LCD_ShowPicture_x2(32,48,63,32,taikongren_4);
		LCD_ShowPicture_x2(32,48,63,32,taikongren_5);
		LCD_ShowPicture_x2(32,48,63,32,taikongren_6);
		LCD_ShowPicture_x2(32,48,63,32,taikongren_7);
		LCD_ShowPicture_x2(32,48,63,32,taikongren_8);
		LCD_ShowPicture_x2(32,48,63,32,taikongren_9);
		LCD_ShowPicture_x2(32,48,63,32,taikongren_10);
//		HAL_Delay(1000);
	}//原图比例放大两倍
		
	if(ChooseShow == 10){
		
		u16 zanting=100;
		LCD_ShowPicture(32,48,63,32,taikongren_1);
		HAL_Delay(zanting);
		LCD_ShowPicture(32,48,63,32,taikongren_2);
		HAL_Delay(zanting);
		LCD_ShowPicture(32,48,63,32,taikongren_3);
		HAL_Delay(zanting);
		LCD_ShowPicture(32,48,63,32,taikongren_4);
		HAL_Delay(zanting);
		LCD_ShowPicture(32,48,63,32,taikongren_5);
		HAL_Delay(zanting);
		LCD_ShowPicture(32,48,63,32,taikongren_6);
		HAL_Delay(zanting);
		LCD_ShowPicture(32,48,63,32,taikongren_7);
		HAL_Delay(zanting);
		LCD_ShowPicture(32,48,63,32,taikongren_8);
		HAL_Delay(zanting);
		LCD_ShowPicture(32,48,63,32,taikongren_9);
		HAL_Delay(zanting);
		LCD_ShowPicture(32,48,63,32,taikongren_10);
		HAL_Delay(zanting);
//		HAL_Delay(1000);
	}//原始图片
	
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
 	
		
  LCD_Init();//LCD初始化
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

	
//    LCD_Show();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  while (1)
  {
		
	
		
   
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
			printf("start");
		
		LCD_Show();
		
//		for(int num;num < 10000;num++){ChooseShow = 1;LCD_Show();ChooseShow = 1;}
		
		
		
//		HAL_Delay(10);
		
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

int fputc(int ch, FILE *f)
{
 uint8_t temp[1] = {ch};
 HAL_UART_Transmit(&huart1, temp, 1, 2);
 return ch;
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
