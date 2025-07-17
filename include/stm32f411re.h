#include <stdint.h>
#include <stdio.h>
#include <gpio.h>
#include <rcc.h>
#include <systick.h>
#include <uart.h>

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
#define GPIOA					0x00
#define GPIOB					0x01
#define GPIOC					0x02
#define GPIOD					0x03
#define GPIOE					0x04
#define GPIOH					0x07

/* USART */
#define USART1_BASE				(0x40011000UL)
#define USART6_BASE				(0x40011400UL)
#define USART2_BASE				(0x40004400UL)

/*
 * Clock
 */

/* Processor Clock rate */
#define SYS_CLK_RATE				16000000

/* Peripherals Clock rate */
#define APB2_CLK_RATE				SYS_CLK_RATE	

