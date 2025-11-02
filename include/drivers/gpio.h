#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdio.h>
#include "stm32f411xe.h"	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>
#include <util.h>

/**
 * @brief Provides a type to hold a GPIO port number or an alias.
 */
typedef uint8_t gpio_port_t;

/**
 * @brief Provides a type to hold GPIO pin number.
 */
typedef uint8_t gpio_pin_t;

/**
 * @brief Provides a type to hold GPIO alternate function.
 */
typedef uint8_t gpio_af_t;

/**
 * @brief Typedef for gpio external interrupt callback function.
 */
typedef void (*gpio_callback_t)(GPIO_TypeDef *gpio);

struct gpio_driver_data {
	gpio_callback_t callback;
};

/**
 * @name GPIO pin configuration flags
 *
 * Different configuration flags can be combined using bitwise OR.
 * A single uint8_t is sufficient to hold all the configurations bits.
 *
 * Example:
 * 	uint8_t cfg = GPIO_MODE_OUTPUT | GPIO_OPEN_DRAIN;
 */

/* GPIO mode flags -  bit position [1:0] */
#define GPIO_MODE_INPUT		(0 << 0)
#define GPIO_MODE_OUTPUT	(1 << 0)
#define GPIO_MODE_AF		(2 << 0)
#define GPIO_MODE_ANALOG	(3 << 0)

/* GPIO output type flags - bit position [2] */
#define GPIO_PUSH_PULL		(0 << 2)
#define GPIO_OPEN_DRAIN		(1 << 2)

/* GPIO output speed flags - bit position [4:3] */
#define GPIO_SPEED_LOW		(0 << 3)
#define GPIO_SPEED_MEDIUM	(1 << 3)
#define GPIO_SPEED_FAST		(2 << 3)
#define GPIO_SPEED_HIGH		(3 << 3)

/* GPIO pull-up/pull-down flags - bit position [6:5] */
#define GPIO_NOPULL			(0 << 5)
#define GPIO_PULL_UP		(1 << 5)
#define GPIO_PULL_DOWN		(2 << 5)

/* Bitmask for extracting each field */
#define GPIO_MODE_MASK		(3 << 0)
#define GPIO_OTYPE_MASK		(1 << 2)
#define GPIO_OSPEED_MASK	(3 << 3)
#define GPIO_PUPD_MASK		(3 << 5)

/* GPIO driver APIs */
void gpio_pin_configure(gpio_port_t port, gpio_pin_t pin, uint8_t flags);
void gpio_pin_af_configure(gpio_port_t port, gpio_pin_t pin, gpio_af_t afx);

static inline uint32_t gpio_pin_get(gpio_port_t port, gpio_pin_t pin) {
	GPIO_TypeDef *gpio = GPIO(port);

	if (gpio->IDR & (1U << pin)) 
		return 1;
	else
		return 0;
}

static inline void gpio_pin_set(gpio_port_t port, gpio_pin_t pin, uint8_t logic_level) {
	GPIO_TypeDef *gpio = GPIO(port);

	if (logic_level) 
		gpio->BSRR = (1U << pin);
	else 
		gpio->BSRR = (1U << (pin + 16));
}

static inline void gpio_pin_toggle(gpio_port_t port, gpio_pin_t pin) {
	GPIO_TypeDef *gpio = GPIO(port);
	gpio->ODR ^= (1U << pin);
}

#endif /* _GPIO_H_ */

