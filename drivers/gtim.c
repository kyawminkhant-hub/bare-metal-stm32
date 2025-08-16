#include <stm32f411re.h>
#include <gtim.h>

static inline void NVIC_EnableIRQ(uint8_t irq_num) {
    NVIC_ISER0[irq_num >> 5] = (1U << (irq_num & 0x1F));
}

static struct gtim_t* gtim_select(struct tim *gtim) 
{
	for (int i = 0; i < NUM_TIMERS; i++) {	
		if (timers[i].gtim == gtim)
            		return &timers[i];
    	}

    	return NULL;
}

void gtim_interrupt_handler(struct tim *gtim)
{
	struct gtim_t *timer = gtim_select(gtim);
	
	if (gtim->SR & TIM_SR_UIF) {
		/* Clear Update Flag */
		gtim->SR &= ~TIM_SR_UIF;
		timer->overflow_count++;
    	}

    	if (timer->overflow_count == timer->reset)
		timer->overflow_count = 0;
}

void gtim_interrupt_enable(struct tim *gtim, uint8_t irq_flag) 
{	
	struct gtim_t *timer = gtim_select(gtim);
	
	if (irq_flag) 
	{
		/* Enable NVIC IRQ */
		NVIC_EnableIRQ(timer->irq_num);
		
		/* Enable Update Interrupt */
		gtim->DIER |= TIM_DIER_UIE;
	}
}

void gtim_counter_start(struct tim *gtim) {
	/* Enable Counter */
	gtim->CR1 |= TIM_CR1_CEN;
}

uint32_t gtim_counter_get(struct tim *gtim) {
	return gtim->CNT;
}

void gtim_configure(struct tim *gtim, uint16_t psc_val, uint32_t arr_val, uint8_t irq_flag)
{		
	/* 
	 * Enable Clock access
	 */
	struct gtim_t *timer = gtim_select(gtim);
	RCC->APB1ENR |= timer->rcc_enable;
		
	/* Enable Interrupt */
	gtim_interrupt_enable(gtim, irq_flag);

	/* Set Prescaler value */
	gtim->PSC = psc_val - 1;

	/* Set Auto-reload value */
	gtim->ARR = arr_val - 1;

	/* Clear Counter */
	gtim->CNT = 0;	
}

void gtim_pwm_configure(struct tim *gtim, uint8_t channel, uint16_t psc_val, uint32_t arr_val, uint32_t ccr_val)
{
	/* Set PSC and ARR value */ 
	gtim_configure(gtim, psc_val, arr_val, 0);

	/* Configure channel-specific PWM Mode 1 */
	switch (channel)
	{
	    case 1:
		gtim->CCR1 = ccr_val;	 
		gtim->CCMR1 &= ~(0xFF);			// Clear OC1M/OC1PE
		gtim->CCMR1 |= (6 << 4) | (1 << 3);	// OC1M = 110 (PWM1), OC1PE = 1
		gtim->CCER |= TIM_CCER_CC1E;		// Enable CC1E 
		break;

	    case 2:
		gtim->CCR2 = ccr_val;
		gtim->CCMR1 &= ~(0xFF00);		// Clear OC2M/OC2PE
		gtim->CCMR1 |= (6 << 12) | (1 << 11);	// OC2M = 110 (PWM1), OC2PE = 1
		gtim->CCER |= TIM_CCER_CC2E;		// Enable CC2E
		break;

	    case 3:
		gtim->CCR3 = ccr_val;
		gtim->CCMR2 &= ~(0xFF);			// Clear OC3M/OC3PE
		gtim->CCMR2 |= (6 << 4) | (1 << 3);	// OC3M = 110 (PWM1), OC3PE = 1
		gtim->CCER |= TIM_CCER_CC3E;		// Enable CC3E
		break;

	    case 4:
		gtim->CCR4 = ccr_val;
		gtim->CCMR2 &= ~(0xFF00);		// Clear OC4M/OC4PE
		gtim->CCMR2 |= (6 << 12) | (1 << 11);	// OC4M = 110 (PWM1), OC4PE = 1
		gtim->CCER |= TIM_CCER_CC4E;		// Enable CC4E
		break;

	    default:
		// Invalid channel
		return;
	}

	/* Enable Auto-Reload Preload */
	gtim->CR1 |= TIM_CR1_ARPE;

	/* Generate update event to apply settings */
	gtim->EGR |= TIM_EGR_UG;
}

void timer_start(struct tim *gtim)
{	
	/*
	 * Prescalar: 16MHz / 1MHz = 16
	 * ARR: 1000 ticks in 1ms 
	 * UEV: intterupt occurs every 1ms (timer overflow)
	 */
	gtim_configure(gtim, SYS_CLK_RATE / TIM_CLK_RATE, 1000, 1);
	
	gtim_counter_start(gtim);
}

void timer_set_ms(struct tim *gtim, uint32_t ms)
{
	struct gtim_t *timer = gtim_select(gtim);
		
	timer->reset = ms;
	
	timer_start(gtim);
}

uint32_t timer_get_ms(struct tim *gtim)
{
	struct gtim_t *timer = gtim_select(gtim);
		
	return timer->overflow_count;
}

void TIM2_IRQHandler(void) {
	gtim_interrupt_handler(TIM2);
}

void TIM3_IRQHandler(void) {
	gtim_interrupt_handler(TIM3);
}

void TIM4_IRQHandler(void) {
	gtim_interrupt_handler(TIM4);
}

void TIM5_IRQHandler(void) {
	gtim_interrupt_handler(TIM5);
}
