#include <hal.h>

#define B1 PINMAP(PC, 13)
#define LD2 PINMAP(PA, 5)

int main(void)
{
	uint8_t reading = 1; // B1 is pulled-up
	
	gpio_pin_configure(B1, GPIO_MODE_INPUT);
	gpio_pin_configure(LD2, GPIO_MODE_OUTPUT);

	while (1) {
		// Polling button state
		reading = gpio_pin_get(B1);
		
		gpio_pin_set(LD2, !reading);
	}

	return 0;
}

