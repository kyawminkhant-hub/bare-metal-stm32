#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdio.h>
#include "stm32f411xe.h" 	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>
#include <gtim.h>

struct timer_driver_data {
        TIM_TypeDef *gtim;
        volatile uint32_t overflow_count;
        volatile uint32_t reset;
};

/* Timer APIs */
void timer_start(TIM_TypeDef *gtim);
void timer_set_ms(TIM_TypeDef *gtim, uint32_t ms);
uint32_t timer_get_ms(TIM_TypeDef *gtim);

#endif /* _TIMER_H_ */ 
