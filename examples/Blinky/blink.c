#include <stm32f411re.h>
#include <gpio.h>
#include <gtim.h>

int main(void)
{
	/* Configure LED (GPIO PB4) as an OUTPUT */
        uint16_t LED = GPIO_INIT(PB, 4); 
	gpio_pin_configure(LED, GPIO_MODE_OUTPUT);

	int duration = 1000;

	timer_start(TIM2);
	
	int last_ms = timer_get_ms(TIM2);


	while(1) {	

		if ((timer_get_ms(TIM2) - last_ms) >= duration) {
			gpio_pin_toggle(LED);
			last_ms = timer_get_ms(TIM2);
		}	
	}
}

