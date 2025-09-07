#include <timer.h>

static struct timer_t* timer_select(struct tim *gtim)
{
	for (int i = 0; i < NUM_TIMERS; i++) {
		if (timers[i].gtim == gtim)
			return &timers[i];
	}
	return NULL;
}

static void timer_callback(struct tim *gtim)
{
	struct timer_t *timer = timer_select(gtim);
	
	if (gtim->SR & TIM_SR_UIF) {
        	/* Clear Update Flag */
		gtim->SR &= ~TIM_SR_UIF;
		timer->overflow_count++;
	}
	
	if (timer->overflow_count == timer->reset)
		timer->overflow_count = 0;
}

void timer_start(struct tim *gtim)
{
	/*
	 * Prescalar: 16MHz / 1MHz = 16
	 * ARR: 1000 ticks in 1ms
	 * UEV: intterupt occurs every 1ms (timer overflow)
	 */
	gtim_configure(gtim, SYS_CLK_RATE / TIM_CLK_RATE, 1000);
	
	gtim_irq_callback_set(gtim, timer_callback);
	gtim_irq_enable(gtim, TIM_INT_UIF);

	gtim_counter_start(gtim);
}

void timer_set_ms(struct tim *gtim, uint32_t ms)
{
	struct timer_t *timer = timer_select(gtim);

	timer->reset = ms;
	timer_start(gtim);
}

uint32_t timer_get_ms(struct tim *gtim)
{
	struct timer_t *timer = timer_select(gtim);

	return timer->overflow_count;
}


