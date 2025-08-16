#ifndef GTIM_H
#define GTIM_H

#include <stm32f411re.h>

#define TIM_CLK_RATE    1000000UL // 1MHz Clock Rate for preconfig
#define NUM_TIMERS      4

/* Timer attributes */
struct gtim_t {
        struct tim *gtim;
        uint8_t irq_num;
        volatile uint32_t rcc_enable;
        volatile uint32_t overflow_count;
        volatile uint32_t reset;
};

static struct gtim_t timers[NUM_TIMERS] = {
        { TIM2, TIM2_IRQn, TIM2EN, 0, 0 },
        { TIM3, TIM3_IRQn, TIM3EN, 0, 0 },
        { TIM4, TIM4_IRQn, TIM4EN, 0, 0 },
        { TIM5, TIM5_IRQn, TIM5EN, 0, 0 },
};

/*
 * GTIM APIs
 */

void gtim_counter_start(struct tim *gtim);
uint32_t gtim_counter_get(struct tim *gtim);

void gtim_configure(struct tim *gtim, uint16_t psc_val, uint32_t arr_val, uint8_t irq_flag);
void gtim_pwm_configure(struct tim *gtim, uint8_t channel, uint16_t psc_val, uint32_t arr_val, uint32_t ccr_val);

void timer_start(struct tim *gtim);
void timer_set_ms(struct tim *gtim, uint32_t ms);
uint32_t timer_get_ms(struct tim *gtim);

#endif /* GTIM_H */ 
