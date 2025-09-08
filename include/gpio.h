#ifndef GPIO_H
#define GPIO_H

#include <stm32f411re.h>

/* 
 * GPIO Helper Macros 
 */
#define GPIO(x)                                 ((struct gpio *)(AHB1PERIPH_BASE + GPIO_OFFSET * x))

/* Store GPIO PORT and pin in a 16-bit variable */
#define GPIO_INIT(PORT, PIN)                    ((PORT << 8) | (PIN))

/* Define PORT in upper byte */
#define PORT(x)                                 (x >> 8)

/* Define PIN in lower byte */
#define PIN(x)                                  (x & 0xFF)

/* GPIO I/O Direction Modes */
enum {
        GPIO_MODE_INPUT,                // 00
        GPIO_MODE_OUTPUT,               // 01
        GPIO_MODE_AF,                   // 10
        GPIO_MODE_ANALOG                // 11
};

/* GPIO alternate functions */
enum {
        AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7,
        AF8, AF9, AF10, AF11, AF12, AF13, AF14, AF15
};

/* GPIO PORT Alias */
enum {
        PA, PB, PC, PD, PE, PH = 7
};

/*
 * GPIO APIs
 */
void gpio_pin_configure(uint16_t pin, uint8_t mode);
void gpio_pin_af_configure(uint16_t pin, uint8_t af_mode);
uint32_t gpio_pin_get(uint16_t pin);
void gpio_pin_toggle(uint16_t pin);
void gpio_pin_set(uint16_t pin, uint8_t logic_level);

#endif 
