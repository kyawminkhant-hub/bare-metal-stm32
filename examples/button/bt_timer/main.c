#include <hal.h>

#define B1 PINMAP(PC, 13)
#define LD2 PINMAP(PA, 5)

/* USER_B1 is pulled-up */
#define B1_RELEASED 1
#define B1_PRESSED  0

int main(void)
{
	/* Configure B1 (GPIO PC13) as an INPUT */
	gpio_pin_configure(B1, GPIO_MODE_INPUT);
	
	/* Configure LED (GPIO PA5) as an OUTPUT */
	gpio_pin_configure(LD2, GPIO_MODE_OUTPUT);

	int bt_state = B1_RELEASED;
	int bt_count = 0;
	int reading = 0;
	int duration = 0;
	int last_ms = 0;

	timer_start(TIM2);
	
	while(1) {
		
		reading = gpio_pin_get(B1);

		if (reading == B1_PRESSED) {

			if (bt_state != reading) {
				bt_state = reading;
				bt_count++;
				last_ms = timer_get_ms(TIM2);
				gpio_pin_toggle(LD2);
			}

			if (bt_count == 1)
				duration = 1000;

			if (bt_count == 2)
				duration = 600;

			if (bt_count == 3) {
				duration = 400;
				bt_count = 0;
			}
		}

		if (reading == B1_RELEASED) {
			bt_state = reading;
		}

		if ((timer_get_ms(TIM2) - last_ms) >= duration) {
			gpio_pin_toggle(LD2);
			last_ms = timer_get_ms(TIM2);
		}	
	}

	return 0;
}

