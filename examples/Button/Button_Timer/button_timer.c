#include <stm32f411re.h>
#include <gpio.h>
#include <timer.h>

// USER_B1 is pulled-up
#define B1_RELEASED 1
#define B1_PRESSED  0

int main(void)
{

    // Configure B1 (GPIO PC13) as an INPUT
    uint16_t B1_PIN = GPIO_INIT(PC, 13);
    gpio_pin_configure(B1_PIN, GPIO_MODE_INPUT);
	
	/* Configure LED (GPIO PA5) as an OUTPUT */
    uint16_t LED = GPIO_INIT(PA, 5); 
	gpio_pin_configure(LED, GPIO_MODE_OUTPUT);

	int bt_state = B1_RELEASED;
	int bt_count = 0;
	int reading = 0;
	int duration = 0;
	int last_ms = 0;

	timer_start(TIM2);
	
	while(1) {
		
		reading = gpio_pin_get(B1_PIN);

		if (reading == B1_PRESSED) {

			if (bt_state != reading) {
				bt_state = reading;
				bt_count++;
				last_ms = timer_get_ms(TIM2);
				gpio_pin_toggle(LED);
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
			gpio_pin_toggle(LED);
			last_ms = timer_get_ms(TIM2);
		}	
	}
}

