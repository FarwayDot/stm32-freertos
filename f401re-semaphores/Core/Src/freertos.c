/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "freertos_defines.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void task_main(void *params)
{
	for(;;)
	{
		vTaskDelete(handle_task_main);
	}
}

void task_green(void *params)
{
	uint8_t cont = 0;

	for(;;)
	{
		if((++cont)>=5)
		{
			cont = 0;
			xSemaphoreGive(handle_semap_sem1);
		}

		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
		osDelay(100);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		osDelay(100);
	}
}

void task_blue(void *params)
{
	uint8_t cont = 0;
	for(;;)
	{
		if(xSemaphoreTake(handle_semap_sem1, portMAX_DELAY) == pdPASS)
		{
			for(cont = 1; cont<=3; cont++)
			{
				HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
				osDelay(50);
				HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
				osDelay(50);
			}
		}
		else
		{

		}
	}
}

void task_red(void *params)
{
	uint8_t cont = 0;
	for(;;)
	{
		if(xSemaphoreTake(handle_semap_sem1, portMAX_DELAY) == pdPASS)
		{
			for(cont = 1; cont<=3; cont++)
			{
				HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
				osDelay(20);
				HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
				osDelay(20);
			}
		}
		else
		{

		}
	}
}



/* USER CODE END Application */

