/*
 * uart.c
 *
 *  Created on: Apr 30, 2026
 *      Author: Sunil Sutar
 */

#include <stm32f446xx.h>
#include "uart.h"


void UART2_GPIO_PinConfig()
{
	//1. Enable Clock for GPIOA
	RCC->AHB1ENR |= (1 << GPIOA_PCLK_EN);

	//2. Set Mode to Alt Fun for GPIO Pins : PA2 : UART_Tx
	GPIOA->MODER &= ~(0x3 << (2 * 2));	//clearing bits
	GPIOA->MODER |= (0x2 << (2 * 2));	//Alf Fun Mode

	//3. Set PA2 Alt Fun Type to USART2_TX => AF7
	GPIOA->AFR[0] &= ~(0xF << (2 * 4));		//clearing bits
	GPIOA->AFR[0] |= (0x7 << (2 * 4));		//Alt Fun = AF7

}

void UART2_Init()
{
	/********** Configure USART GPIO Pins ***********/
	UART2_GPIO_PinConfig();

	/********** Configure USART Module *************/
	//1. Enable Clock for USART2
	RCC->APB1ENR |= (1 << UART2_PCLK_EN);

	//2. Configure UART Buadrate
	USART2->BRR = 0x88;

	//3. Configure the transfer direction
	USART2->CR1 |= (1 << USART2_CR1_TE);

	 //4. Enable UART Module
	USART2->CR1 |= (1 << USART2_CR1_UE);

}

void UART2_SendChar(char ch)
{
	//1. Wait until TXE Flag is Set
	while( ! (USART2->SR & (1 << USART2_SR_TXE)));

	//2. write data to DR
	USART2->DR = ch;
}

void UART2_SendString(char *str)
{
	while(*str)
	{
		UART2_SendChar(*str++);
	}
}
