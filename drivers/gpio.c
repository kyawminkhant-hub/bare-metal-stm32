#include <stdio.h>
#include "stm32f411xe.h"		// CMSIS Device Specific
#include <stm32f411re.h>		// Board Specs Declarations
#include <hal_conf.h>
#include <util.h>
#include <gpio.h>

#define GPIO_DRIVER_INIT(index)																\
    static struct gpio_driver_data gpio##index##_driver_data = {							\
        .callback = NULL,                     												\
																							\
    };																						\
																							\
	void GPIO##index##_IRQHandler(void) {													\
    	if (gpio##index##_driver_data.callback) {											\
        	gpio##index##_driver_data.callback(GPIO(index));								\
    	}																					\
	}												
																							
#define FOREACH_GPIO(M)																		\
    M(0) 																					\
    M(1)																					\
    M(2)																					\
	M(3)																					\
	M(4)																					\
	M(7)

FOREACH_GPIO(GPIO_DRIVER_INIT)

void gpio_pin_configure(gpio_port_t port, gpio_pin_t pin, uint8_t flags)	
{
	GPIO_TypeDef *gpio = GPIO(port);

	uint8_t mode = (flags & GPIO_MODE_MASK) >> 0;
	uint8_t otype = (flags & GPIO_OTYPE_MASK) >> 2;
	uint8_t ospeed = (flags & GPIO_OSPEED_MASK) >> 3;
	uint8_t pupd = (flags & GPIO_PUPD_MASK) >> 5;

	/* Enable RCC Clock */
	RCC->AHB1ENR |= (1U << port); 

	/* Configure GPIO Mode */
	gpio->MODER &= ~(3U << (2 * pin));
	gpio->MODER |=  (mode << (2 * pin));

	/* Configure GPIO Output Type */
	gpio->OTYPER &= ~(1U << pin);
	gpio->OTYPER |=  (otype << pin);

	/* Configure GPIO Output Speed */
	gpio->OSPEEDR &= ~(3U << (2 * pin));
	gpio->OSPEEDR |=  (ospeed << (2 * pin)); 

	/* Configure GPIO Pull Up Pull Down */
	gpio->PUPDR &= ~(3U << (2 * pin));
	gpio->PUPDR |=  (pupd << (2 * pin));
}

void gpio_pin_af_configure(gpio_port_t port, gpio_pin_t pin, gpio_af_t afx)
{	
	GPIO_TypeDef *gpio = GPIO(port);

	/* Configure GPIO Alternate Function */
	gpio->AFR[pin >> 3] &= ~(15U << ((pin & 7) * 4));
	gpio->AFR[pin >> 3] |=  ((afx & 15U) << ((pin & 7) * 4));
}

