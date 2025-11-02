#ifndef _PWM_H_
#define _PWM_H_

#include <stdio.h>
#include "stm32f411xe.h" 	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>
#include <gtim.h>

/* PWM APIs */
void pwm_configure(TIM_TypeDef *gtim, struct gtim_config *cfg);
void pwm_set(TIM_TypeDef *gtim, uint8_t channel, uint32_t dc_percent, uint32_t freq);

#endif /*_PWM_H_ */

