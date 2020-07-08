/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "BspConfig.h"
#include "usart.h"
/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
Customerinfo meSportInfo = { 0 };
Customerinfo   *ptMsg;
uint16_t TempCount = 0, SportCount = 0;
/* TIM2 init function */
void MX_TIM2_Init(uint16_t per)        //定时器2             
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 71;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = per;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

	if (tim_baseHandle->Instance == TIM2)
	{

		__HAL_RCC_TIM2_CLK_ENABLE();
		HAL_NVIC_SetPriority(TIM2_IRQn, 5, 4);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
	}
	else if (tim_baseHandle->Instance == TIM3) //定时器3
	{
		__HAL_RCC_TIM3_CLK_ENABLE();
		HAL_NVIC_SetPriority(TIM3_IRQn, 2, 3);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);

	}
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{
	if (tim_baseHandle->Instance == TIM2)
	{
		__HAL_RCC_TIM2_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM2_IRQn);
	}
	else if (tim_baseHandle->Instance == TIM3)
	{
		__HAL_RCC_TIM3_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM3_IRQn);
	}
}

/* USER CODE BEGIN 1 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint16_t timer2_T_Period = 0, waitTim = 0;
	static uint32_t tick = 0;////////////////////////////////
	BaseType_t xResult;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	ptMsg = &meSportInfo;
	if (htim->Instance == TIM2)
	{
		if (timer2_T_Period++>TIMER_ALL_PERIOD)
		{
			timer2_T_Period = 0;
			if (PERIOD_DO_EXECUTE(tick, TEST_SENSOR_DATA)) //检测频率
			{
				//Uartx_printf(&huart2, "Timer2=%d", tick);
				ptMsg->freq = TempCount;
				TempCount = 0;

				//运动时间累加
				if (ptMsg->freq > 0)
				{ 
					ptMsg->tim++;
					//Uartx_printf(&huart1, "Freq=%d,SportCount=%d", ptMsg->freq, SportCount);
				}
				else
				{
					if (waitTim++>5)
					{
						waitTim = 0;
						if (SportCount!=0)
						{
							Uartx_printf(&huart1, "Begin play...\r\n");
							ptMsg->playstate = 1;//播放标志位置位
							SportCount = 0;
						}
						
					}
					//Uartx_printf(&huart1, "waiTim=%d", waitTim);       //检测用
				}
				
			}
			tick++;
		}
	}
}

void SensorCallBack(uint8_t v)//计次回调函数
{
	//Uartx_printf(&huart1, "HelloButton!\r\n");
	TempCount++;
	SportCount++;
	//在此处向串口屏发送数据
	Uart_printf(&huart1, "Freq=%d      SportCount=%d", ptMsg->freq, SportCount);
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
