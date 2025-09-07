#include <gtim.h>

void gtim_configure(struct tim *gtim, uint16_t psc_val, uint32_t arr_val)
{		
	/* Enable Clock access */
	if (gtim == TIM2)
		RCC->APB1ENR |= TIM2EN;
	else if (gtim == TIM3)
		RCC->APB1ENR |= TIM3EN;	
	else if (gtim == TIM4)
		RCC->APB1ENR |= TIM4EN;
	else if (gtim == TIM5)
		RCC->APB1ENR |= TIM5EN;
		    
	/* Set Prescaler value */
	gtim->PSC = psc_val - 1;

	/* Set Auto-reload value */
	gtim->ARR = arr_val - 1;

	/* Clear Counter */
	gtim->CNT = 0;	
}

void gtim_pwm_configure(struct tim *gtim, uint8_t channel, 
	uint16_t psc_val, uint32_t arr_val, uint32_t ccr_val)
{    
	/* Set PSC and ARR value */ 
	gtim_configure(gtim, psc_val, arr_val);

	/* Configure channel-specific PWM Mode 1 */
	switch (channel) {
	case 1:
		gtim->CCR1 = ccr_val;	 
		gtim->CCMR1 &= ~(0xFF);	// Clear OC1M/OC1PE
		gtim->CCMR1 |= (6 << 4) | (1 << 3); // OC1M = 110 (PWM1), OC1PE = 1
		gtim->CCER |= TIM_CCER_CC1E; // Enable CC1E 
		break;
	case 2:
		gtim->CCR2 = ccr_val;
		gtim->CCMR1 &= ~(0xFF00); // Clear OC2M/OC2PE
		gtim->CCMR1 |= (6 << 12) | (1 << 11); // OC2M = 110 (PWM1), OC2PE = 1
		gtim->CCER |= TIM_CCER_CC2E; // Enable CC2E
		break;
	case 3:
		gtim->CCR3 = ccr_val;
		gtim->CCMR2 &= ~(0xFF);	// Clear OC3M/OC3PE
		gtim->CCMR2 |= (6 << 4) | (1 << 3); // OC3M = 110 (PWM1), OC3PE = 1
		gtim->CCER |= TIM_CCER_CC3E; // Enable CC3E
		break;
	case 4:
		gtim->CCR4 = ccr_val;
		gtim->CCMR2 &= ~(0xFF00); // Clear OC4M/OC4PE
		gtim->CCMR2 |= (6 << 12) | (1 << 11); // OC4M = 110 (PWM1), OC4PE = 1
		gtim->CCER |= TIM_CCER_CC4E; // Enable CC4E
		break;
	default:
		return; // Invalid channel
	}

	/* Enable Auto-Reload Preload */
	gtim->CR1 |= TIM_CR1_ARPE;

	/* Generate update event to apply settings */
	gtim->EGR |= TIM_EGR_UG;
}

void gtim_irq_enable(struct tim *gtim, gtim_irq_flag_t flag) 
{	
	/* Enable NVIC IRQ */
	if (gtim == TIM2)
		NVIC_EnableIRQ(TIM2_IRQn);
	else if (gtim == TIM3)
		NVIC_EnableIRQ(TIM3_IRQn);	
	else if (gtim == TIM4)
		NVIC_EnableIRQ(TIM4_IRQn);	
	else if (gtim == TIM5)
		NVIC_EnableIRQ(TIM5_IRQn);	

	/* Enable corresponding TIM Interrupt */
	switch (flag) {
	case TIM_INT_UIF:
		gtim->DIER |= TIM_DIER_UIE;
		break;
	case TIM_INT_CC1F:
		gtim->DIER |= TIM_DIER_CC1IE;
		break;
	case TIM_INT_CC2F:
		gtim->DIER |= TIM_DIER_CC2IE;
		break;
	case TIM_INT_CC3F:
		gtim->DIER |= TIM_DIER_CC3IE;
		break;
	case TIM_INT_CC4F:
		gtim->DIER |= TIM_DIER_CC4IE;
		break;
	case TIM_INT_TIF:
		gtim->DIER |= TIM_DIER_TIE;
		break;
	default:
		break;
	}
}

void gtim_irq_callback_set(struct tim *gtim, gtim_callback_t callback)
{
	/* Add callback functions to corresponding TIM ISR */
	if (gtim == TIM2) 
		tim2_callback = callback;
	else if (gtim == TIM3)
		tim3_callback = callback;
	else if (gtim == TIM4)
		tim4_callback = callback;
	else if (gtim == TIM5)
		tim5_callback = callback;
}

void TIM2_IRQHandler(void) {
	tim2_callback(TIM2);
}

void TIM3_IRQHandler(void) {
	tim3_callback(TIM3);
}

void TIM4_IRQHandler(void) {
	tim4_callback(TIM4);
}

void TIM5_IRQHandler(void) {
	tim5_callback(TIM5);
}
