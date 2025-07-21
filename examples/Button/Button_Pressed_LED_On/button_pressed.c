/*
 * This example code shows how to debounce a button using blocking delay.
 */

#include <stdint.h>
#include <stm32f411re.h>

// USER_B1 is pulled-up
#define B1_RELEASED		1
#define B1_PRESSED		0

int main(void)
{
        // Configure B1 (GPIO PC13) as an INPUT
        uint16_t B1_PIN = GPIO_INIT(GPIOC, 13);
	gpio_pin_configure(B1_pin, GPIO_MODE_INPUT);
        
	// Configure LED (GPIO PA5) as an OUTPUT
        uint16_t LD2_pin = GPIO_INIT(GPIOA, 5);
        gpio_pin_configure(LD2_pin, GPIO_MODE_OUTPUT);

        unsigned int bt_state = B1_RELEASED;	
	unsigned int last_bt_state = B1_RELEASED;
	
	while (1)
        {
		// Polling button state
		bt_state = gpio_pin_get(B1_pin);
		
		if (bt_state)
			gpio_pin_set(LD2_pin, 0);
		else
			gpio_pin_set(LD2_pin, 1);
	}
}

