#include <gpio.h>

void gpio_pin_configure(uint16_t pin, uint8_t mode)
{
	struct gpio *gpio = GPIO(PORT(pin));
 	uint8_t n = PIN(pin);

	RCC->AHB1ENR |= (1U << PORT(pin)); 

	gpio->MODER &= ~(3 << (2 * n));
	gpio->MODER |= (mode & 3) << (2 * n);
}

void gpio_pin_af_configure(uint16_t pin, uint8_t af_mode)
{
	struct gpio *gpio = GPIO(PORT(pin));
	uint8_t n = PIN(pin);
	gpio->AFR[n >> 3] &= ~(15UL << ((n & 7) * 4));
	gpio->AFR[n >> 3] |= (af_mode << ((n & 7) * 4));
}

uint32_t gpio_pin_get(uint16_t pin)
{
	struct gpio *gpio = GPIO(PORT(pin));
	uint8_t n = PIN(pin);
        
	if (gpio->IDR & (1U << n)) 
		return 1;
	else
		return 0;
}

void gpio_pin_set(uint16_t pin, uint8_t logic_level)
{
	struct gpio *gpio = GPIO(PORT(pin));
	uint8_t n = PIN(pin);

	if (logic_level) 
		gpio->BSRR = (1U << n);
	else 
        	gpio->BSRR = (1U << (n + 16));
}

void gpio_pin_toggle(uint16_t pin)
{
	struct gpio *gpio = GPIO(PORT(pin));
	uint8_t n = PIN(pin);
	gpio->ODR ^= (1U << n);
}
