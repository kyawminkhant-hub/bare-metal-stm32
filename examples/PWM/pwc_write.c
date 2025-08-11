#include <stm32f411re.h>
#include <gpio.h>
#include <gtim.h>
#include <systick.h>
#include <pwm.h>


int main(void) 
{
	int pwm_freq = 1000;

	/* Configure GPIO pin as PWM (AF2 - TIM3_CH1) */
	uint16_t LED = GPIO_INIT(PB, 4);
	gpio_pin_configure(LED, GPIO_MODE_AF);
	gpio_pin_af_configure(LED, AF2);

        while (1) {
		for (int duty_cycle = 0; duty_cycle < 100; duty_cycle++) {
			pwm_set(TIM3, 1, duty_cycle, pwm_freq);
			delay_ms(100);
		}	
		
		for (int duty_cycle = 100; duty_cycle > 0; duty_cycle--) {
			pwm_set(TIM3, 1, duty_cycle, pwm_freq);
			delay_ms(100);
		}

	}
}

