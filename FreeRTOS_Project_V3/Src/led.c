/*
 * led.c
 *
 *  Created on: May 2, 2026
 *      Author: Sunil Sutar
 */

#include <stm32f446xx.h>
#include "led.h"

void LED_Init(void)
{
	/* Enable GPIOA clock */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/* Set PA5 as output */
	GPIOA->MODER &= ~(0x3 << (5 * 2));		//clearing
	GPIOA->MODER |= (0x1 << (5 * 2));		//output

}

void LED_On(void)
{
	GPIOA->ODR |= (1 << LED_PIN);
}

void LED_Off(void)
{
	GPIOA->ODR &= ~(1 << LED_PIN);
}
