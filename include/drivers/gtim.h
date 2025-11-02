#ifndef _GTIM_H_
#define _GTIM_H_

#include <stdio.h>
#include "stm32f411xe.h"	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>
#include <util.h>

/* Typedef for general-purpose TIM interrupt callback functions */
typedef void (*gtim_callback_t)(TIM_TypeDef *gtim);

/**
 * @brief struct for general-purpose TIM peripheral configurations
 *
 * This struct instance is used to represent configuarations
 * for each general-purpose TIM peripheral
 * 
 * @param channel Timer channel
 * @param prescaler Prescaler value
 * @param auto_reload Auto-reload value
 * @param preload Capture/Compare value
 */
struct gtim_config {
	uint8_t channel;
	uint16_t prescaler;
	uint32_t auto_reload;
	uint32_t preload;
};

struct gtim_driver_data {
	gtim_callback_t callback;
};

/* General-purpose TIM Interrupt Flags */
typedef enum {
	TIM_INT_UIF, 
	TIM_INT_CC1F, 
	TIM_INT_CC2F,
	TIM_INT_CC3F,
	TIM_INT_CC4F,
	TIM_INT_TIF
} gtim_irq_flag_t; 

/* General-purpose TIM APIs */
static inline void gtim_rcc_enable(TIM_TypeDef *gtim) {	
	if (gtim == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if (gtim == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;	
	else if (gtim == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	else if (gtim == TIM5)
		RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
 }

static inline void gtim_configure(TIM_TypeDef *gtim, struct gtim_config *cfg) {
	/* Enable clock access */
	gtim_rcc_enable(gtim);

	/* Set Prescaler value */
	gtim->PSC = cfg->prescaler - 1;

	/* Set Auto-reload value */
	gtim->ARR = cfg->auto_reload - 1;

	/* Clear Counter */
	gtim->CNT = 0;	
}

static inline void gtim_counter_start(TIM_TypeDef *gtim) {
        gtim->CR1 |= TIM_CR1_CEN;
}

static inline uint32_t gtim_counter_get(TIM_TypeDef *gtim) {
        return gtim->CNT;
}

void gtim_irq_callback_set(TIM_TypeDef *gtim, gtim_callback_t callback);
void gtim_irq_enable(TIM_TypeDef *gtim, gtim_irq_flag_t flag);

#endif /* _GTIM_H_ */ 
