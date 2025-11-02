#include <hal.h>

#define LD2	PINMAP(PA, 5)

int main(void)
{
	gpio_pin_configure(LD2, GPIO_MODE_OUTPUT);

	while(1) {	
		gpio_pin_toggle(LD2);
		delay_ms(1000);
	}

	return 0;
}

