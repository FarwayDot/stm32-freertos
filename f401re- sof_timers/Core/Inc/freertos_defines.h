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
extern TimerHandle_t oneShotHandle;
extern TimerHandle_t repeatHandle;
extern TimerHandle_t handle_timer_user;


/*Functions*/
void oneShotCallBack(TimerHandle_t  xTimer);
void repeatCallBack(TimerHandle_t  xTimer);
void timer_user_callback(TimerHandle_t  xTimer);

#endif /* INC_FREERTOS_DEFINES_H_ */
