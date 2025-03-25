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
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define PRUEBA_YIELD
//#define PRUEBA_SEMAP_2
//#define PRUEBA_POLLING
//#define PRUEBA_TIME_BOUND
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
volatile uint32_t flag = 0;
/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
static void lookBusy( uint32_t numIterations );
void Blinking_led(GPIO_TypeDef *gpio, uint8_t pin);
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
#ifdef PRUEBA_SEMAP_2
		/*Código con 2 semáforos*/
		if(xSemaphoreTake(handle_semap_sem1, portMAX_DELAY) == pdPASS)
		{
			for(cont = 0; cont < 5; cont++)
			{
				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
				osDelay(150);
				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
				osDelay(150);
			}
			xSemaphoreGive(handle_semap_sem2);
		}
#endif

#ifdef PRUEBA_YIELD
		/*Código con taskYIELD*/
		if(xSemaphoreTake(handle_semap_sem1, portMAX_DELAY) == pdPASS)
		{
			for(cont = 0; cont < 5; cont++)
			{
				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
				osDelay(150);
				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
				osDelay(150);
			}
			xSemaphoreGive(handle_semap_sem1);
			taskYIELD();
		}
#endif

#ifdef PRUEBA_POLLING

		if(++cont>5)
		{
			cont = 0;
			flag = 1;
		}
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
		osDelay(150);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		osDelay(150);

#endif

#ifdef PRUEBA_TIME_BOUND
		uint8_t numLoops = (rand() % (7 + 1))+3;
		/*Blinking at 5Hz 50%*/
		if(++cont >= numLoops)
		{
			cont=0;
			xSemaphoreGive(handle_semap_sem1);
		}
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
		osDelay(100);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		osDelay(100);
		/**/

#endif
#ifdef HIGH_PRIORITY_EXAMPLE
		if(xSemaphoreTake(handle_semap_sem1, pdMS_TO_TICKS(200))== pdPASS)
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			Blinking_led(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
			xSemaphoreGive(handle_semap_sem1);
		}
		else
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		}

		osDelay((rand()%(30-5+1))+5);

#endif
	}
}

void task_blue(void *params)
{
	uint32_t cont = 0;
	for(;;)
	{
#ifdef PRUEBA_SEMAP_2
		/*Código con 2 semáforos*/
		if(xSemaphoreTake(handle_semap_sem2, portMAX_DELAY) == pdPASS)
		{
			for(cont = 1; cont<=3; cont++)
			{
				HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
				osDelay(25);
				HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
				osDelay(25);
			}
			xSemaphoreGive(handle_semap_sem1);
		}
#endif

#ifdef PRUEBA_YIELD
		/*Código con taskYIELD*/

        if(xSemaphoreTake(handle_semap_sem1, portMAX_DELAY) == pdPASS)
        {
            for(cont = 0; cont < 3; cont++)
            {
                HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
                osDelay(25);
                HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
                osDelay(25);
            }
            xSemaphoreGive(handle_semap_sem1);
            taskYIELD();
        }
#endif

#ifdef PRUEBA_POLLING
        /*Código con polling*/
        if(flag!=0)
        {
        	for(cont = 1; cont <= 3; cont++)
        	{
                HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
                osDelay(25);
                HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
                osDelay(25);
        	}
        	flag = 0;
        }
#endif

#ifdef PRUEBA_TIME_BOUND
        if(xSemaphoreTake(handle_semap_sem1, pdMS_TO_TICKS(500))==pdPASS)
		{
        	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
        	for(uint8_t i=1; i<=3; i++)
        	{
        		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
				osDelay(50);
				HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
				osDelay(50);
        	}
		}
        else
        {
        	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
        }
#endif

#ifdef HIGH_PRIORITY_EXAMPLE

		osDelay(((rand()%(25-10+1))+10));
		cont = (rand()%(750000-250000+1))+250000;
		lookBusy(cont);

#endif
	}
}

void task_red(void *params)
{
	uint8_t cont = 0;
	for(;;)
	{

#ifdef PRUEBA_TIME_BOUND
		vTaskDelete(handle_task_red);
#endif

#ifdef HIGH_PRIORITY_EXAMPLE
	if(xSemaphoreTake(handle_semap_sem1, pdMS_TO_TICKS(200))==pdPASS)
	{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		Blinking_led(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		xSemaphoreGive(handle_semap_sem1);
	}
	else
	{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	}
#endif

	}
}


void Blinking_led(GPIO_TypeDef *gpio, uint8_t pin)
{
	for(uint8_t i=1; i<=2; i++)
	{
		HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
		osDelay(43);
		HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
		osDelay(43);
	}
}

static void lookBusy( uint32_t numIterations )
{
	__attribute__((unused))volatile uint32_t dontCare = 0;
	for(int i = 0; i < numIterations; i++)
	{
		dontCare = i % 4;
	}
}

/* USER CODE END Application */

