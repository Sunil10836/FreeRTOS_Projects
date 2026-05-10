/*
 * app_tasks.h
 *
 *  Created on: May 2, 2026
 *      Author: HP
 */

#ifndef APP_TASKS_H_
#define APP_TASKS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

#include "adc.h"
#include "led.h"

typedef struct
{
	char msg[64];
}LogMessage_t;

void vTemperatureTask(void *pvParameters);
void vControllerTask(void *pvParameters);
void vLoggerTask(void *pvParameters);

void vLogTimerCallback(TimerHandle_t xTimer);

#endif /* APP_TASKS_H_ */
