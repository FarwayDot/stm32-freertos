/*
 * freertos_defines.h
 *
 *  Created on: Mar 13, 2025
 *      Author: User
 */

#ifndef INC_FREERTOS_DEFINES_H_
#define INC_FREERTOS_DEFINES_H_

#include "main.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "event_groups.h"

/*Defines*/


/*Structures and enums*/
typedef enum
{
	SYS_READY 	= 1<<0,
	SYS_ERROR 	= 1<<1,
	SYS_TASK_A 	= 1<<2,
	SYS_TASK_B 	= 1<<3,
	SYS_TASK_BUTTON = 1<<4
}event_flags_e;

typedef enum{
    BUTTON_FREE = 0,
    BUTTON_DEBOUNCE,
    BUTTON_ONPRESS,
    BUTTON_KEEPALIVE,
    BUTTON_ONRELEASE,
}app_button_state_n;

typedef struct  app_button
{
	GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t state;
}app_button_t;

/*Variables*/

extern TaskHandle_t handle_task_main;
extern TaskHandle_t handle_task_green;
extern TaskHandle_t handle_task_blue;
extern TaskHandle_t handle_task_red;
extern TaskHandle_t handle_task_button;

extern SemaphoreHandle_t handle_count_semap_1;
extern EventGroupHandle_t handle_event_1;

/*Functions*/
void task_green(void *params);
void task_blue(void *params);
void task_red(void *params);
void button_task_read_entry(void *params);

#endif /* INC_FREERTOS_DEFINES_H_ */
