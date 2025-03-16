/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "mpu6050.h"

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



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

////////////////数据采集	

extern Kalman_t KalmanX, KalmanY;
double anlge_x = 0;
double anlge_y = 0;
double anlge_z = 0;
double angle_x0 = 0;//测试用
double angle_y0 = 0;
double angle_z0 = 0;
		
double gyro_x = 0;
double gyro_y = 0;
double gyro_z = 0;

    MPU6050_t mpu6050;
		
void GetGyroOffsets(float* gyroX_offset, float* gyroY_offset, float* gyroZ_offset) {
    
    float x = 0;
    float y = 0;
    float z = 0;
	
	    MPU6050_Read_All(&hi2c2, &mpu6050);
	
    for(int i = 0; i < 1000; i++) { // 读取2000次数据求平均值
        MPU6050_Read_All(&hi2c2, &mpu6050);
        x += mpu6050.Gx;
        y += mpu6050.Gy;
        z += mpu6050.Gz;
        HAL_Delay(1);
    }
    *gyroX_offset = x / 1000;
    *gyroY_offset = y / 1000;
    *gyroZ_offset = z / 1000;
}


void SG90_Mpu6050_View(double angle_x){//直接输出
	
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,angle_x*1000+1500);
	

}

void SG90_Mpu6050_Angle(double angle_x){//角度输出
	
	double result = (angle_x+180) * (2000.0/360.0) + 500;
	
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,result);
	

}


#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}

void SG90_Test()
	{
		int delay_sg90_test=1000; //循环时间间隔1s
      
      //★舵机指向0°
      __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,500); //相当于一个周期内（20ms）有0.5ms高脉冲
      HAL_Delay(delay_sg90_test);
		//★舵机指向90°
      __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1500); //相当于一个周期内（20ms）有0.5ms高脉冲
      HAL_Delay(delay_sg90_test);
      //★舵机指向180°
      __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,2500); //相当于一个周期内（20ms）有2.5ms高脉冲
      HAL_Delay(delay_sg90_test);
	
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	
	float gyroX_offset = 0;
	float gyroY_offset = 0;
	float gyroZ_offset = 0;

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
  MX_TIM4_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
		
	MPU6050_Init(&hi2c2);//陀螺仪初始化
	GetGyroOffsets(&gyroX_offset, &gyroY_offset, &gyroZ_offset);//零漂处理
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);//初始化完成


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		/////////////////////////////////////////
		
		// Read MPU6050 data
    MPU6050_Read_All(&hi2c2, &mpu6050);
		
		mpu6050.Gx -= gyroX_offset;
    mpu6050.Gy -= gyroY_offset;
    mpu6050.Gz -= gyroZ_offset;
		
		// Calculate Kalman angle for X and Y
//		anlge_x = Kalman_getAngle(&KalmanX, anlge_x, mpu6050.Gx, 0.01);
		anlge_y = Kalman_getAngle(&KalmanY, mpu6050.Ay, mpu6050.Gy, 0.02);
		angle_y0= mpu6050.Gy*0.02+angle_y0;
		
		// Print Kalman angles to console
//		printf("Kalman X angle = %lf\r\n", anlge_x);
//		printf("Kalman Y angle = %lf\r\n", anlge_y);
		
//		printf("channels: 1.386578,0.977929,-0.628913,-0.942729\n");
		printf("Kalman Y angle : %lf,%lf\r\n",anlge_y,angle_y0);
		
		
		////////////////////////////////////////
//		SG90_Test();
		SG90_Mpu6050_Angle(anlge_y);
//		SG90_Mpu6050_View(mpu6050.Ay);
//		printf("[main] tofo : aaa");
		
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
