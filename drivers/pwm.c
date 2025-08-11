#include <pwm.h>
#include <gtim.h>

void pwm_set(struct tim *gtim, uint8_t channel, uint32_t dc_percent, uint32_t freq)
{
	/*
         * Prescalar[Fixed]: 16MHz / 1MHz = 16 (1 tick = 1us) 
         * ARR: 1MHz / frequency (eg. 1MHz / 1000Hz = 1000 ticks)
         * CCR: (Duty Cycle * ARR) / 100 (eg. 50/100 x 1000 = 500 ticks)
         */
	uint16_t psc_val = SYS_CLK_RATE / TIM_CLK_RATE;
	uint32_t arr_val = TIM_CLK_RATE / freq;
	uint32_t ccr_val = (dc_percent * arr_val) / 100;

	gtim_pwm_configure(gtim, channel, psc_val, arr_val, ccr_val);

	gtim_counter_start(gtim);
}
