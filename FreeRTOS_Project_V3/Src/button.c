/*
 * button.c
 *
 *  Created on: May 4, 2026
 *      Author: Sunil Sutar
 */

#include <stm32f446xx.h>
#include "button.h"

#define NVIC_ISER1   (*(volatile unsigned int*)0xE000E104)
#define NVIC_IPR10 	 (*(volatile unsigned int*)0xE000E428)

void Button_GPIO_EXTI_Init()
{
	/* 1. Enable GPIOC and SYSCFG clock */
	RCC->AHB1ENR |= (1 << 2);
	RCC->APB2ENR |= (1 << 14);

	/* 2. Set PC13 as intput */
	GPIOC->MODER &= ~(0x3 << (13 * 2));

	/* 3. Set pull-up*/
	GPIOC->PUPDR &= ~(0x3 << (13 * 2));		//clearing
	GPIOC->PUPDR |= (0x1 << (13 * 2));		//pull-up

	 /* 4. Connect EXTI13 line to PC13 */
	SYSCFG->EXTICR[3] &= ~(0xF << 4);		// Clear EXTI13 config
	SYSCFG->EXTICR[3] |= (0x2 << 4);		// PC = 0010

	 /* 5. Configure EXTI Line 13 */
	EXTI->IMR |= (1 << 13);					// Interrupt unmask
	EXTI->FTSR |= (1 << 13);				// Falling edge trigger (button press)
	EXTI->RTSR &= ~(1 << 13);				// Disable rising edge

	//Clear Pending Flag
	EXTI->PR |= (1 << 13);   // Clear any pending interrupt

	 /* 6. Enable EXTI15_10 Interrupt in NVIC */
	NVIC_ISER1 |= (1 << (40 - 32));  // IRQ40 → EXTI15_10
	NVIC_IPR10 |= (5 << 4);   // 5 : safe priority (medium priority 0-high to 15-Low)

}


