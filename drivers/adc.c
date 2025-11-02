#include <stdio.h>
#include "stm32f411xe.h"		// CMSIS Device Specific
#include <stm32f411re.h>		// Board Specs Declarations
#include <hal_conf.h>
#include <util.h>
#include <gpio.h>
#include <adc.h>

void adc_mode_select(ADC_TypeDef *adc, adc_mode_t mode)
{
	// TODO: Add more modes

	switch (mode) {
	case ADC_MODE_SIN:
		adc->CR2 &= ~ADC_CR2_CONT;   // Disable continuous
		break;
	case ADC_MODE_CONT:
		adc->CR2 |= ADC_CR2_CONT;    // Enable continuous
		break;
	default:
		break; 
	}
}

void adc_configure(ADC_TypeDef *adc, uint8_t channel, adc_mode_t mode)
{	
	// TODO: Set Multiple Conversion Sequence
	
	/* Enable ADC1 Clock */
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	/* Set Single Conversion Sequence */ 
	adc->SQR3 = channel;
	adc->SQR1 = 0;

	/* Select ADC Mode */
	adc_mode_select(adc, mode);	

	/* Enable ADC1 Module */
	adc->CR2 |= ADC_CR2_ADON;
}

uint32_t adc_get(ADC_TypeDef *adc)
{
	adc->CR2 |= ADC_CR2_SWSTART; // Start conversion
	while (!(adc->SR & ADC_SR_EOC)); // Wait conversion
	return adc->DR;
}
