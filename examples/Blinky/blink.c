#include <stm32f411re.h>
#include <gpio.h>
#include <systick.h>

int main(void)
{
	/* Configure LED (GPIO PA5) as an OUTPUT */
	uint16_t LED = GPIO_INIT(PA, 5); 
	gpio_pin_configure(LED, GPIO_MODE_OUTPUT);

	while(1) {	
		gpio_pin_toggle(LED);
		delay_ms(1000);
	}

	return 0;
}

