#ifndef GTIM_H
#define GTIM_H

#include <stm32f411re.h>

/* 
 * GTIM Interrupt Flags
 */
typedef enum {
	TIM_INT_UIF, 
	TIM_INT_CC1F, 
	TIM_INT_CC2F,
	TIM_INT_CC3F,
	TIM_INT_CC4F,
	TIM_INT_TIF
} gtim_irq_flag_t; 

/* 
 * GTIM Callback Init 
 */
typedef void (*gtim_callback_t)(struct tim *gtim);

static gtim_callback_t tim2_callback;
static gtim_callback_t tim3_callback;
static gtim_callback_t tim4_callback;
static gtim_callback_t tim5_callback;

/*
 * GTIM APIs
 */
void gtim_configure(struct tim *gtim, uint16_t psc_val, uint32_t arr_val);

void gtim_pwm_configure(struct tim *gtim, uint8_t channel, uint16_t psc_val, uint32_t arr_val, uint32_t ccr_val);

void gtim_irq_callback_set(struct tim *gtim, gtim_callback_t callback);

void gtim_irq_enable(struct tim *gtim, gtim_irq_flag_t flag);

static inline void gtim_counter_start(struct tim *gtim) {
        gtim->CR1 |= TIM_CR1_CEN;
}

static inline uint32_t gtim_counter_get(struct tim *gtim) {
        return gtim->CNT;
}


#endif /* GTIM_H */ 
