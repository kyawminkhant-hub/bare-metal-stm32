#ifndef TIMER_H
#define TIMER_H

#include <stm32f411re.h>
#include <gtim.h>

#define TIM_CLK_RATE	1000000UL // 1MHz Clock Rate for preconfigured APIs
#define NUM_TIMERS      4

/* 
 * Timer Structs 
 */
struct timer_t {
        struct tim *gtim;
        volatile uint32_t overflow_count;
        volatile uint32_t reset;
};

static struct timer_t timers[NUM_TIMERS] = {
        { TIM2, 0, 0 },
        { TIM3, 0, 0 },
        { TIM4, 0, 0 },
        { TIM5, 0, 0 },
};

/*
 * Timer APIs
 */
void timer_start(struct tim *gtim);
void timer_set_ms(struct tim *gtim, uint32_t ms);
uint32_t timer_get_ms(struct tim *gtim);

#endif /* TIMER_H */ 
