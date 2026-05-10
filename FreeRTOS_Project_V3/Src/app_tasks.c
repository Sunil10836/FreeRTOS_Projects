/*
 * app_tasks.c
 *
 *  Created on: May 2, 2026
 *      Author: Sunil Sutar
 */

#include <stdio.h>
#include "app_tasks.h"
#include "led.h"
#include "uart.h"

extern QueueHandle_t tempQueue;
extern QueueHandle_t logQueue;
extern SemaphoreHandle_t uartMutex;
extern SemaphoreHandle_t xButtonSemaphore;

/* Temperature Task (Producer) */

void vTemperatureTask(void *pvParameters)
{
	uint16_t adc_value;
	float temperature;

	while(1)
	{
		adc_value = ADC_Read();

		temperature = Get_Temperature(adc_value);

		xQueueOverwrite(tempQueue, &temperature);

		//printf("Temp Sent: %.2f\r\n", temperature);

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

/* Control Task (Consumer) */

void vControllerTask(void *pvParameters)
{
	float temperature;

	while(1)
	{
		if(xQueuePeek(tempQueue, &temperature, portMAX_DELAY))
		{
			//printf(" vControllerTask : Temperature : %.2f\r\n", temperature);

			if(temperature > 30.0f)	//50
				LED_On();
			else
				LED_Off();
		}

		//Button
		if(xSemaphoreTake(xButtonSemaphore, 0))
		{
			LED_On();
		}

		 vTaskDelay(pdMS_TO_TICKS(100));
	}
}

/* Logger Task */

void vLoggerTask(void *pvParameters)
{
	LogMessage_t log;

	while(1)
	{
		if(xQueueReceive(logQueue, &log, portMAX_DELAY))
		{
			xSemaphoreTake(uartMutex, portMAX_DELAY);
			printf("vLoggerTask : %s\r\n", log.msg);
			xSemaphoreGive(uartMutex);
		}
		else
		{
			printf("No Msg\r\n");
		}
	}
}

/* ================= TIMER CALLBACK ================= */

void vLogTimerCallback(TimerHandle_t xTimer)
{
	LogMessage_t log;
	float temperature;

	if(xQueuePeek(tempQueue, &temperature, 0) == pdPASS)
	{
		snprintf(log.msg, sizeof(log.msg), "Temperature = %.2f C\r\n", temperature);

		//printf("vLogTimerCallback : Message : %s\n", log.msg);

		xQueueSend(logQueue, &log, 0);

	}
}

