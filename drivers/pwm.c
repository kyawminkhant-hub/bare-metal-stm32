#include <stdio.h>
#include "stm32f411xe.h" 	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>
#include <gtim.h>
#include <pwm.h>

void pwm_configure(TIM_TypeDef *gtim, struct gtim_config *cfg)
{    
	/* Configure general-purpose TIM */ 
	gtim_configure(gtim, cfg);

	/* Configure channel-specific PWM Mode 1 */
	switch (cfg->channel) {
	case 1:
		gtim->CCR1 = cfg->preload;	 
		gtim->CCMR1 &= ~(0xFF);	// Clear OC1M/OC1PE
		gtim->CCMR1 |= (6 << 4) | (1 << 3); // OC1M = 110 (PWM1), OC1PE = 1
		gtim->CCER |= TIM_CCER_CC1E; // Enable CC1E 
		break;
	case 2:
		gtim->CCR2 = cfg->preload;
		gtim->CCMR1 &= ~(0xFF00); // Clear OC2M/OC2PE
		gtim->CCMR1 |= (6 << 12) | (1 << 11); // OC2M = 110 (PWM1), OC2PE = 1
		gtim->CCER |= TIM_CCER_CC2E; // Enable CC2E
		break;
	case 3:
		gtim->CCR3 = cfg->preload;
		gtim->CCMR2 &= ~(0xFF);	// Clear OC3M/OC3PE
		gtim->CCMR2 |= (6 << 4) | (1 << 3); // OC3M = 110 (PWM1), OC3PE = 1
		gtim->CCER |= TIM_CCER_CC3E; // Enable CC3E
		break;
	case 4:
		gtim->CCR4 = cfg->preload;
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

void pwm_set(TIM_TypeDef *gtim, uint8_t channel, uint32_t dc_percent, uint32_t freq)
{
	/*
	 * Prescalar[Fixed]: 16MHz / 1MHz = 16 (1 tick = 1us) 
	 * ARR: 1MHz / frequency (eg. 1MHz / 1000Hz = 1000 ticks)
	 * CCR: (Duty Cycle * ARR) / 100 (eg. 50/100 x 1000 = 500 ticks)
	 */
	struct gtim_config pwm_cfg;

	pwm_cfg.channel = channel;
	pwm_cfg.prescaler = SYS_CLK_RATE / TIM_CLK_RATE;
	pwm_cfg.auto_reload = TIM_CLK_RATE / freq;
	pwm_cfg.preload = (dc_percent * pwm_cfg.auto_reload) / 100;

	pwm_configure(gtim, &pwm_cfg);
	gtim_counter_start(gtim);
}
