#ifndef PWM_H
#define PWM_H

#include <stm32f411re.h>
#include <gtim.h>
#include <timer.h>

/*
 * PWM APIs
 */
void pwm_set(struct tim *gtim, uint8_t channel, uint32_t dc_percent, uint32_t freq);

#endif /*PWM_H */

