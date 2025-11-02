#include <stdio.h>
#include "stm32f411xe.h" 	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>
#include <gtim.h>
#include <timer.h>

#define NUM_TIMERS 4

static struct timer_driver_data timers[NUM_TIMERS] = {
        { TIM2, 0, 0 },
        { TIM3, 0, 0 },
        { TIM4, 0, 0 },
        { TIM5, 0, 0 },
};

static struct timer_driver_data* timer_select(TIM_TypeDef *gtim)
{
	for (int i = 0; i < NUM_TIMERS; i++) {
		if (timers[i].gtim == gtim)
			return &timers[i];
	}
	return NULL;
}

static void timer_callback(TIM_TypeDef *gtim)
{
	struct timer_driver_data *timer = timer_select(gtim);
	
	if (gtim->SR & TIM_SR_UIF) {
        /* Clear Update Flag */
		gtim->SR &= ~TIM_SR_UIF;
		
		timer->overflow_count++;
	}
	
	if (timer->overflow_count == timer->reset)
		timer->overflow_count = 0;
}

void timer_start(TIM_TypeDef *gtim)
{
	/*
	 * Prescalar: 16MHz / 1MHz = 16
	 * ARR: 1000 ticks in 1ms
	 * UEV: intterupt occurs every 1ms (timer overflow)
	 */
	struct gtim_config timer_cfg;
	
	timer_cfg.prescaler = SYS_CLK_RATE / TIM_CLK_RATE;
	timer_cfg.auto_reload = 1000;

	gtim_configure(gtim, &timer_cfg);
	gtim_irq_callback_set(gtim, timer_callback);
	gtim_irq_enable(gtim, TIM_INT_UIF);
	gtim_counter_start(gtim);
}

void timer_set_ms(TIM_TypeDef *gtim, uint32_t ms)
{
	struct timer_driver_data *timer = timer_select(gtim);

	timer->reset = ms;
	timer_start(gtim);
}

uint32_t timer_get_ms(TIM_TypeDef *gtim)
{
	struct timer_driver_data *timer = timer_select(gtim);

	return timer->overflow_count;
}


