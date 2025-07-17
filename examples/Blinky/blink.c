#include <stdint.h>
#include <stm32f411re.h>

int main(void)
{
        // Configure LED (GPIO PA5) as an OUTPUT
        uint16_t LD2_pin = GPIO_INIT(GPIOA, 5);
        gpio_pin_configure(LD2_pin, GPIO_MODE_OUTPUT);

        while(1)
        {
		gpio_pin_toggle(LD2_pin);
		ms_delay(1000);
	}
}

