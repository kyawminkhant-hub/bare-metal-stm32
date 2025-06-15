#include <stdint.h>
#include <stm32f411re.h>

// Define bit mask for enabling GPIOAEN and GPIOCEN in RCC_AHB1EN register
#define GPIOAEN		(1U << 0)
#define GPIOCEN		(1U << 2)

int main(void)
{
        // Enable clock access to GPIOA & GPIOC
        RCC->AHB1ENR |= GPIOAEN;
        RCC->AHB1ENR |= GPIOCEN;

        // Configure LED (GPIO PA5) as an OUTPUT
        uint16_t LD2_PIN = GPIO_INIT('A', 5);
        gpio_pin_configure(LD2_PIN, GPIO_MODE_OUTPUT);

        while(1)
        {
		gpio_pin_toggle(LD2_PIN);
		ms_delay(1000);
	}
}

