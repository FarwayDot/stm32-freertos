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

//Sempahore handle

//Mutex handle

//Queue handle
extern QueueHandle_t ledCmdQueue;

//Task handle
extern TaskHandle_t handle_task_receiv;
extern TaskHandle_t	handle_task_send;

/*Functions*/
void recvTask(void *params);
void sendingTask(void *params);

#endif /* INC_FREERTOS_DEFINES_H_ */
