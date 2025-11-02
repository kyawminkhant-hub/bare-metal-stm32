#ifndef _ADC_H_
#define _ADC_H_

#include <stdio.h>
#include "stm32f411xe.h"		// CMSIS Device Specific
#include <stm32f411re.h>		// Board Specs Declarations
#include <hal_conf.h>
#include <util.h>
#include <gpio.h>

/* ADC Modes */
typedef enum {
	ADC_MODE_SIN,
	ADC_MODE_CONT,
	ADC_MODE_SCAN,
	ADC_MODE_DISC
} adc_mode_t;

/* ADC APIs */
void adc_configure(ADC_TypeDef *adc, uint8_t channel, adc_mode_t mode);

uint32_t adc_get(ADC_TypeDef *adc);

static inline uint32_t adc_get_percent(ADC_TypeDef *adc) {
	return (adc_get(adc) * 100) / ADC_RESOLUTION;
}

#endif /* _ADC_H_ */

