/*
 * This example code shows how to debounce a button using blocking delay.
 */

#include <stm32f411re.h>
#include <gpio.h>

/* USER_B1 is pulled-up */
#define B1_RELEASED		1
#define B1_PRESSED		0

int main(void)
{
	/* Configure B1 (GPIO PC13) as an INPUT */
	uint16_t B1_PIN = GPIO_INIT(PC, 13);
	gpio_pin_configure(B1_PIN, GPIO_MODE_INPUT);
        
	/* Configure LED (GPIO PA5) as an OUTPUT */
	uint16_t LD2_PIN = GPIO_INIT(PA, 5);
	gpio_pin_configure(LD2_PIN, GPIO_MODE_OUTPUT);

        uint8_t reading = B1_RELEASED;	
	
	while (1) {
		// Polling button state
		reading = gpio_pin_get(B1_PIN);
		
		gpio_pin_set(LD2_PIN, !reading);
	}

	return 0;
}

