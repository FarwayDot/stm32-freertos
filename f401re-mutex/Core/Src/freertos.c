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
static void Blinking_led(GPIO_TypeDef *gpio, uint8_t pin);
static void lookBusy( uint32_t numIterations );
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
	//uint8_t cont = 0;

	for(;;)
	{
		if(xSemaphoreTake(handle_mutex_1, pdMS_TO_TICKS(200)) == pdPASS)
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			Blinking_led(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
			xSemaphoreGive(handle_mutex_1);
		}
		else
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		}
		osDelay((rand()%(30-5+1))+5); //Delay entre 5 y 30 ms
	}
}

void task_blue(void *params)
{
	uint32_t cont = 0;
	for(;;)
	{
		osDelay((rand()%(25-10+1))+10);
		cont = (rand()%(750000-250000+1))+250000;
		lookBusy(cont);
	}
}

void task_red(void *params)
{
	for(;;)
	{
		if(xSemaphoreTake(handle_mutex_1, pdMS_TO_TICKS(200)) == pdPASS)
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			Blinking_led(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
			xSemaphoreGive(handle_mutex_1);
		}
		else
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		}
	}
}

void button_task_read_entry(void *params)
{
	app_button_t *obj;
	obj = (app_button_t *)params;

	//uint8_t cont = 0;
	uint8_t state;
	uint8_t pin_read = 0;
	uint32_t ticks = 0;

	//osEventFlagsWait(handle_event_1, SYS_READY, osFlagsWaitAny, osWaitForever);

	for(;;)
	{
		vTaskDelete(handle_task_button);
		pin_read = HAL_GPIO_ReadPin(obj->port, obj->pin);
		state = obj->state;
		switch(state)
		{
			case BUTTON_FREE:
				/*Action*/

				/*Si detecta que se presiona (En 0)*/
				if(pin_read == GPIO_PIN_RESET)
				{
					vTaskDelay(pdMS_TO_TICKS(30));
					obj->state = BUTTON_DEBOUNCE;
				}
				break;

			case BUTTON_DEBOUNCE:
				/*Action*/

				/*Si se mantiene presionado*/
				if(pin_read == GPIO_PIN_RESET)
				{
					ticks = xTaskGetTickCount();
					obj->state = BUTTON_ONPRESS;
				}
				else /*Si se suelta rápidamente*/
				{
					//Event
					obj->state = BUTTON_ONRELEASE;
				}
				break;

			case BUTTON_ONPRESS:
				/*Action*/

				/*Confirmando que sigue presionado*/
				if(pin_read == GPIO_PIN_RESET)
				{
					/*Esperamos un tiempo*/
					if((xTaskGetTickCount() - ticks) >= pdMS_TO_TICKS(2000))
					{
						obj->state = BUTTON_KEEPALIVE;
					}

				}
				else /*Si se soltó el botón*/
				{
					obj->state = BUTTON_ONRELEASE;
				}
				break;

			case BUTTON_KEEPALIVE:
				/*Action*/

				/*Si soltamos el botón*/
				if(pin_read == GPIO_PIN_SET)
				{
					/*Cambiamos a on_release*/
					obj->state = BUTTON_ONRELEASE;
				}
				break;

			case BUTTON_ONRELEASE:
				/*Action*/
				xSemaphoreGive(handle_count_semap_1);

				/*Volvemos a FREE*/
				obj->state = BUTTON_FREE;
				break;
			default:
				break;
		}
		vTaskDelay(pdMS_TO_TICKS(20));
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

