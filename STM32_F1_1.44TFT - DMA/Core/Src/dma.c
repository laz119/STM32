/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
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
#include "dma.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure DMA                                                              */
/*----------------------------------------------------------------------------*/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}

/* USER CODE BEGIN 2 */

//void dma1_to_spi1(DMA_Channel_TypeDef* dma_chanel, u32 buf_size, uint16_t spi_dma_req, uint32_t dma_flag) {
//	//����һ����ʱ����
//	u16 timeout = 0;
//	
//	//���³�ʼ��DMA��������С��ʹ�� DMA ͨ��
//	dma1_chanel_choose(DMA1_Channel3, 128*2);

//	//ʹ�� DMA1
//	SPI_I2S_DMACmd(SPI1, spi_dma_req, ENABLE);

//	//�ж� DMA �Ƿ�������ݴ��䣬������һ��ʱ�ޣ����жϱ��δ���
//	while(DMA_GetFlagStatus(dma_flag) == RESET) {
//		if(timeout ++ > 200) break;
//	}

//	// ��� DMA ��־λ
//	DMA_ClearFlag(dma_flag);
//}


/* USER CODE END 2 */

