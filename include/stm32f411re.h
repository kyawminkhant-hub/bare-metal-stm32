#include <stdint.h>
#include <gpio.h>
#include <rcc.h>
#include <systick.h>

/*
 * Peripheral Register Addresses
 */

/* Peripheral Base Address */
#define PERIPH_BASE                             (0x40000000UL)

/* AHB1 Bus Addresses */
#define AHB1PERIPH_OFFSET                       (0x00020000UL)
#define AHB1PERIPH_BASE                         (PERIPH_BASE + AHB1PERIPH_OFFSET)

/* Cortex-M4 Internal Peripherals */
#define SYST_BASE				(0xE000E010UL)

/* RCC */
#define RCC_OFFSET                              (0x3800UL)
#define RCC_BASE                                (AHB1PERIPH_BASE + RCC_OFFSET)

/* GPIO */
#define GPIO_OFFSET                             (0x400UL)

/*
 * Processor Clock
 */

/* Clock rate */
#define SYS_CLK_RATE				16000000
