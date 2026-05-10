/*
 * main.c
 *
 *  Created on: May 4, 2026
 *      Author: Sunil Sutar
 */

#include <stm32f446xx.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include  "button.h"

#include "app_tasks.h"
#include "timers.h"

uint32_t SystemCoreClock = 16000000;

QueueHandle_t tempQueue;
QueueHandle_t logQueue;
SemaphoreHandle_t uartMutex;
SemaphoreHandle_t xButtonSemaphore;
TimerHandle_t logTimer;

int main()
{
	UART2_Init();
	ADC1_Init();
	LED_Init();
	Button_GPIO_EXTI_Init();

	/*Create 2 Queues*/
	tempQueue = xQueueCreate(1, sizeof(float));
	logQueue = xQueueCreate(10, sizeof(LogMessage_t));

	/*Create Mutex for  UART */
	uartMutex = xSemaphoreCreateMutex();

	/*Create Binary Semaphore */
	xButtonSemaphore = xSemaphoreCreateBinary();

	/*Create Software Timer*/
	logTimer = xTimerCreate("Log Timer", pdMS_TO_TICKS(2000), pdTRUE, NULL, vLogTimerCallback);

	/* Create 3 Tasks */
	xTaskCreate(vTemperatureTask, "Temperature Task", 256, NULL, 2, NULL);
	xTaskCreate(vControllerTask, "Controller Task", 256, NULL, 2, NULL);
	xTaskCreate(vLoggerTask, "Logger Task", 256, NULL, 1, NULL);

	/*Start Software Timer*/
	xTimerStart(logTimer, 0);

	/*Start Scheduler*/
	vTaskStartScheduler();

	while(1)
	{

	}

	return 0;
}

void EXTI15_10_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWaken = pdFALSE;

	if(EXTI->PR & (1 << 13))
	{
		EXTI->PR |= (1 << 13);	 // clear pending

		/* Give semaphore */
		xSemaphoreGiveFromISR(xButtonSemaphore, &xHigherPriorityTaskWaken);

		portYIELD_FROM_ISR(xHigherPriorityTaskWaken);
	}
}

int _write(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        while (!(USART2->SR & (1 << 7))); // TXE
        USART2->DR = ptr[i];
    }
    return len;
}
