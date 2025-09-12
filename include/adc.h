#ifndef ADC_H
#define ADC_H

#include <stm32f411re.h>
#include <gpio.h>

#define ADC_RES	4095

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

static inline uint32_t adc_get_percent(struct adc *adc) {
	return (adc_get(adc) * 100) / ADC_RES;
}

#endif /* ADC_H */

