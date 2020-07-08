/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "usart.h"
#include "APPTooL.h"
#include "tim.h"
#include "BspConfig.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
QueueHandle_t xQueuel_sportmes;//消息队列  ，在tim.h中声明
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId DataDetectionHandle;
osThreadId Uart_TFTHandle;
osThreadId DataInteractionHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void PlayCallback(uint8_t val);//语音播放回调函数
Customerinfo SportInfo_Get = { 0 };   //获取到的运动信息
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void DataDetection_CallBack(void const * argument);
void Uart_TFT_CallBack(void const * argument);
void DataInteraction_CallBack(void const * argument);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */


/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

 

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
	/* definition and creation of DataDetection */
	taskENTER_CRITICAL();//进入临界区
	xQueuel_sportmes = xQueueCreate(5, sizeof(struct SportInfo*));//创建消息队列
	if (xQueuel_sportmes == 0)
	{
		Error_Handler_t(ERROR_XQUEUE_CREAT);
	}
	osThreadDef(DataDetection, DataDetection_CallBack, osPriorityNormal, 0, 128);
	DataDetectionHandle = osThreadCreate(osThread(DataDetection), NULL);

	/* definition and creation of Uart_TFT */
	osThreadDef(Uart_TFT, Uart_TFT_CallBack, osPriorityNormal, 0, 128);
	Uart_TFTHandle = osThreadCreate(osThread(Uart_TFT), NULL);

	/* definition and creation of DataInteraction */
	osThreadDef(DataInteraction, DataInteraction_CallBack, osPriorityNormal, 0, 128);
	DataInteractionHandle = osThreadCreate(osThread(DataInteraction), NULL);
	
  /* Infinite loop */
	Uart_printf(&huart1, "Start sub stask\r\n");
	vTaskDelete(defaultTaskHandle); //删除任务
	taskEXIT_CRITICAL();//推出临界区
	
    osDelay(100);
  
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_DataDetection_CallBack */
/**
* @brief Function implementing the DataDetection thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DataDetection_CallBack */
void DataDetection_CallBack(void const * argument)
{
  /* USER CODE BEGIN DataDetection_CallBack */
  /* Infinite loop */
	Customerinfo *ptMsg;
	BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(1000); /* 设置最大等待时间为200ms */
  for(;;)
  {
	 
	  xResult = xQueueReceive(
		  xQueuel_sportmes,                   /* 消息队列句柄 */
		  (void *)&ptMsg,             /* 这里获取的是结构体的地址 */
		  (TickType_t)xMaxBlockTime);/* 设置阻塞时间 */

	  if (xResult == pdPASS)
	  {
		 // Uart_printf(&huart1, "Freq=%d, Tim=%d ,Sportcount=%d, Cal=%d  playstate=%d", ptMsg->freq, ptMsg->tim, ptMsg->count,ptMsg->hot,ptMsg->playstate);
		  SportInfo_Get.count = ptMsg->count;
		  SportInfo_Get.freq = ptMsg->freq;
		  SportInfo_Get.hot = ptMsg->hot;
		  SportInfo_Get.tim = ptMsg->tim;
		  SportInfo_Get.playstate = ptMsg->playstate;

		  SingleTrig(PlayCallback, ptMsg->playstate, 0, 0, 1);
	  }
	 // Uartx_printf(&huart1, "thread2\r\n");
    osDelay(200);
  }
  /* USER CODE END DataDetection_CallBack */
}

/* USER CODE BEGIN Header_Uart_TFT_CallBack */
/**
* @brief Function implementing the Uart_TFT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Uart_TFT_CallBack */
void Uart_TFT_CallBack(void const * argument)
{
  /* USER CODE BEGIN Uart_TFT_CallBack */
  /* Infinite loop */
  for(;;)
  {
	  SingleTrig(SensorCallBack, HAL_GPIO_ReadPin(Sensor_Mag_GPIO_Port, Sensor_Mag_Pin), 0, 1, 0);
	  //Uart_printf(&huart1, "Uart2\r\n");
    osDelay(50);
  }
  /* USER CODE END Uart_TFT_CallBack */
}

/* USER CODE BEGIN Header_DataInteraction_CallBack */
/**
* @brief Function implementing the DataInteraction thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DataInteraction_CallBack */
void DataInteraction_CallBack(void const * argument)
{
  /* USER CODE BEGIN DataInteraction_CallBack */
  /* Infinite loop */
  for(;;)
  {
	  //Uartx_printf(&huart1, "thread4\r\n");
	  if (uart1_rec.reover == 1)
	  {
		  uart1_rec.reover = 0;
		  Uart_printf(&huart1, uart1_rec.redata); //等待蓝牙信息

	  }
	  if (uart2_rec.reover == 1)
	  {
		  uart2_rec.reover = 0;
		  Uart_printf(&huart2, uart2_rec.redata); //等待蓝牙信息

	  }
    osDelay(100);
  }
  /* USER CODE END DataInteraction_CallBack */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void vApplicationIdleHook(void)
{
	static uint16_t x = 0;
}
void PlayCallback(uint8_t val)//语音播放回调函数
{
	Uart_printf(&huart1, "playstate=%d   Sound is beginning...!\r\n",SportInfo_Get.playstate);
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
