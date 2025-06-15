#ifndef GPIO_H
#define GPIO_H

#include <stm32f411re.h>

// Map PORT name and  base address of GPIO 
#define GPIO(x)                                 ((struct gpio *)(AHB1PERIPH_BASE + GPIO_OFFSET * x))
// Store GPIO PORT and pin in a 16-bit variable
#define GPIO_INIT(PORT, PIN)                    (((PORT - 'A') << 8) | (PIN))
// Define PORT in upper byte
#define PORT(x)                                 (x >> 8)
// Define PIN in lower byte
#define PIN(x)                                  (x & 0xFF)

/* 
 * GPIO Registers
 */
struct gpio {
        volatile uint32_t MODER;    // Offset 0x00
        volatile uint32_t OTYPER;   // Offset 0x04
        volatile uint32_t OSPEEDR;  // Offset 0x08
        volatile uint32_t PUPDR;    // Offset 0x0C
        volatile uint32_t IDR;      // Offset 0x10
        volatile uint32_t ODR;      // Offset 0x14
        volatile uint32_t BSRR;     // Offset 0x18
        volatile uint32_t LCKR;     // Offset 0x1C
        volatile uint32_t AFR[2];   // Offset 0x20 and 0x24
};

/* 
 * GPIO I/O Direction Modes
 */ 
enum {
        GPIO_MODE_INPUT,        // 00
        GPIO_MODE_OUTPUT,       // 01
        GPIO_MODE_AF,           // 10
        GPIO_MODE_ANALOG        // 11
};

/*
 * GPIO APIs
 */
void gpio_pin_configure(uint16_t pin, uint8_t mode);

uint32_t gpio_pin_get(uint16_t pin);

void gpio_pin_toggle(uint16_t pin);
void gpio_pin_set(uint16_t pin, uint8_t logic_level);

#endif 
