#ifndef ADC_H
#define ADC_H

#include <stm32f411re.h>
#include <gpio.h>

/* 
 * ADC Modes 
 */
typedef enum {
	ADC_MODE_SIN,
	ADC_MODE_CONT,
	ADC_MODE_SCAN,
	ADC_MODE_DISC
} adc_mode_t;

/*
 * ADC APIs
 */
void adc_configure(struct adc *adc, uint8_t channel, adc_mode_t mode);
uint32_t adc_get(struct adc *adc);
uint32_t adc_get_percent(struct adc *adc);

#endif /* ADC_H */

