/*
 * adc.c
 *
 *  Created on: May 4, 2026
 *      Author: Sunil Sutar
 */

#include <stm32f446xx.h>
#include "adc.h"

/*
 * Temperature Sensor => ADC1_IN18
 */
void ADC1_Init(void)
{
	/* 1. Enable ADC1 Clock */
	RCC->APB2ENR |= (1 << ADC1_CLK_EN);

	/*2 .Temperature sensor and VREFINT enable : ADC_CCR */
	ADC->CCR |= (1 << ADC1_CCR_TSVREFE);

	/* 3 . Long Sample */
	ADC1->SMPR1 |= (7 << 24);

	/* 4. Regular sequence length = 1 */
    ADC1->SQR1 = 0;

    /* 5. Select channel 18 (temp sensor) */
	ADC1->SQR3 = 18;

	/* 6. Enable ADC */
	ADC1->CR2 |= (1 << ADC1_CR2_ADON);

	/* 7. Stabilization delay */
	delay(10000);
}

uint16_t ADC_Read(void)
{
	/* Start ADC Conversion */
	ADC1->CR2 |= (1 << ADC1_CR2_SWSTART);

	/*Wait until flag is set*/
	while(! (ADC1->SR & (1 << ADC1_SR_EOC)));

	/*return adc value*/
	return (uint16_t)ADC1->DR;
}

float Get_Temperature(uint16_t adc_value)
{
	float Vsense = (adc_value * 3.3f) / 4096.0f;

	/* Datasheet formula (approx) */
	float temperature = ((Vsense - 0.76f) / 0.0025f) + 25.0f;

	return temperature;
}

void delay(volatile uint32_t count)
{
    while(count--);
}

