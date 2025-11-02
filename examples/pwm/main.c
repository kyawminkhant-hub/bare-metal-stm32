#include <hal.h>

#define LED         PINMAP(PB, 4)
#define PWM_FREQ    1000    

int main(void) {
	/* Configure GPIO pin as PWM (AF2 - TIM3_CH1) */
	gpio_pin_configure(LED, GPIO_MODE_AF);
	gpio_pin_af_configure(LED, AF2);

    while (1) {
        for (int duty_cycle = 0; duty_cycle < 100; duty_cycle++) {
            pwm_set(TIM3, 1, duty_cycle, PWM_FREQ);
            delay_ms(100);
        }   	

        for (int duty_cycle = 100; duty_cycle > 0; duty_cycle--) {
            pwm_set(TIM3, 1, duty_cycle, PWM_FREQ);
            delay_ms(100);
        }
    }

    return 0;
}

