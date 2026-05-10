/*
 * adc.h
 *
 *  Created on: May 4, 2026
 *      Author: Sunil Sutar
 */

#ifndef ADC_H_
#define ADC_H_

#define ADC1_CLK_EN				8

#define ADC1_CR2_ADON			0
#define ADC1_CR2_SWSTART		30
#define ADC1_CCR_TSVREFE		23
#define ADC1_SR_EOC				1

void ADC1_Init(void);
uint16_t ADC_Read(void);
float Get_Temperature(uint16_t value);
void delay(volatile uint32_t count);

#endif /* ADC_H_ */
