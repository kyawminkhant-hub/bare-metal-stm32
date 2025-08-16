/*
 * This example code shows how to debounce a button using non-blocking delay.
 */

#include <stm32f411re.h>
#include <gpio.h>
#include <gtim.h>

// USER_B1 is pulled-up
#define B1_RELEASED		1
#define B1_PRESSED		0

int main(void)
{
        // Configure B1 (GPIO PC13) as an INPUT
        uint16_t B1_PIN = GPIO_INIT(PC, 13);
	gpio_pin_configure(B1_PIN, GPIO_MODE_INPUT);

        // Configure LED (GPIO PA5) as an OUTPUT
        uint16_t LD2_PIN = GPIO_INIT(PA, 5);
        gpio_pin_configure(LD2_PIN, GPIO_MODE_OUTPUT);

        unsigned int bt_state = B1_RELEASED;	
	unsigned int last_reading = B1_RELEASED;
	unsigned int last_ms = 0;
	unsigned int duration = 20;

	timer_start(TIM2);
	
	while (1)
        {
		// Polling button state
		int reading = gpio_pin_get(B1_PIN);

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
					gpio_pin_toggle(LD2_PIN);
			}
		}

		last_reading = reading;
	}
}

