/*
 * This example code shows how to debounce a button using non-blocking delay.
 */
#include <hal.h>

#define B1 PINMAP(PC, 13)
#define LD2 PINMAP(PA, 5)

/* USER_B1 is pulled-up */
#define B1_RELEASED	1
#define B1_PRESSED	0

int main(void)
{
	/* Configure B1 (GPIO PC13) as an INPUT */
	gpio_pin_configure(B1, GPIO_MODE_INPUT);

	/* Configure LED (GPIO PA5) as an OUTPUT */
 	gpio_pin_configure(LD2, GPIO_MODE_OUTPUT);

	unsigned int bt_state = B1_RELEASED;	
	unsigned int last_reading = B1_RELEASED;
	unsigned int last_ms = 0;
	unsigned int duration = 20;

	timer_start(TIM2);
	
	while (1) {
		// Polling button state
		int reading = gpio_pin_get(B1);

		/*
		 * If button state changes, due to the noise or pressing
		 */
		if (reading != last_reading) {
			last_ms = timer_get_ms(TIM2);
		}

		/*
		 * If the button state is the same after delay, the button is pressed
		 * Whenever button is pressed, toggle LED               
		 */
		if ((timer_get_ms(TIM2) - last_ms) > duration) {

			if (bt_state != reading) {
				bt_state = reading;

				if (bt_state == B1_PRESSED)
					gpio_pin_toggle(LD2);
			}
		}
		last_reading = reading;
	}

	return 0;
}

