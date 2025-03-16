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


/*Variables*/

extern TaskHandle_t handle_task_main;
extern TaskHandle_t handle_task_green;
extern TaskHandle_t handle_task_blue;
extern TaskHandle_t handle_task_red;

extern SemaphoreHandle_t handle_semap_sem1;
extern SemaphoreHandle_t handle_semap_sem2;

/*Functions*/
void task_green(void *params);
void task_blue(void *params);
void task_red(void *params);

#endif /* INC_FREERTOS_DEFINES_H_ */
