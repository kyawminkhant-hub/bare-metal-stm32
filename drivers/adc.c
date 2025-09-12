#include <adc.h>

void adc_mode_select(struct adc *adc, adc_mode_t mode)
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

void adc_configure(struct adc *adc, uint8_t channel, adc_mode_t mode)
{	
	// TODO: Set Multiple Conversion Sequence
	
	/* Enable ADC1 Clock */
	RCC->APB2ENR |= ADC1EN;

	/* Set Single Conversion Sequence */ 
	adc->SQR3 = channel;
	adc->SQR1 = 0;

	/* Select ADC Mode */
	adc_mode_select(adc, mode);	

	/* Enable ADC1 Module */
	adc->CR2 |= ADC_CR2_ADON;
}

uint32_t adc_get(struct adc *adc)
{
	adc->CR2 |= ADC_CR2_SWSTART; // Start conversion
	while (!(adc->SR & ADC_SR_EOC)); // Wait conversion
	return adc->DR;
}
