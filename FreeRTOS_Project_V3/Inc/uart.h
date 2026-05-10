/*
 * uart.h
 *
 *  Created on: Apr 30, 2026
 *      Author: Sunil Sutar
 */

#ifndef UART_H_
#define UART_H_

#define GPIOA_PCLK_EN			0
#define UART2_PCLK_EN			17

#define USART2_CR1_TE		3
#define USART2_CR1_UE		13
#define USART2_SR_TXE		7

void UART2_GPIO_PinConfig();
void UART2_Init();
void UART2_SendChar(char ch);
void UART2_SendString(char *str);

#endif /* UART_H_ */
