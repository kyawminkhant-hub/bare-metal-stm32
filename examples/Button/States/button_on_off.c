/*
 * This example code shows how to debounce a button using blocking delay.
 */

#include <stdint.h>
#include <stm32f411re.h>

// Define bit mask for enabling GPIOAEN and GPIOCEN in RCC_AHB1EN register
#define GPIOAEN			(1U << 0)
#define GPIOCEN			(1U << 2)

// USER_B1 is pulled-up
#define B1_RELEASED		1
#define B1_PRESSED		0

int main(void)
{
        // Enable clock access to GPIOA & GPIOC
        RCC->AHB1ENR |= GPIOAEN;
        RCC->AHB1ENR |= GPIOCEN;

        // Configure B1 (GPIO PC13)
        uint16_t B1_PIN = GPIO_INIT('C', 13);

        // Configure LED (GPIO PA5) as an OUTPUT
        uint16_t LD2_PIN = GPIO_INIT('A', 5);
        gpio_pin_configure(LD2_PIN, GPIO_MODE_OUTPUT);

        unsigned int bt_state = B1_RELEASED;	
	unsigned int last_bt_state = B1_RELEASED;
	
	while (1)
        {
		// Polling button state
		bt_state = gpio_pin_get(B1_PIN);
		
		if (bt_state)
			gpio_pin_set(LD2_PIN, 0);
		else
			gpio_pin_set(LD2_PIN, 1);
	}
}

