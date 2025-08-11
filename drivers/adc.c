#include <gpio.h>
#include <adc.h>

void adc_mode_select(struct adc *adc, uint8_t mode)
{
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

void adc_configure(struct adc *adc, uint8_t channel, uint8_t mode)
{	
	/* Enable ADC1 Clock */
	RCC->APB2ENR |= ADC1EN;

	/* Set Single Conversion Sequence */ 
	// TODO: Multiple Conversion Sequence
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
	while (!(adc->SR & ADC_SR_EOC)) {} // Wait conversion
	return adc->DR;
}

uint32_t adc_get_percent (struct adc *adc) {
	return (adc_get(adc) * 100) / 4095;
}
