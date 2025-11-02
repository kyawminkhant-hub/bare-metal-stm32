#ifndef _STM32F411RE_H_
#define _STM32F411RE_H_

#include <stdint.h>
#include <stdio.h>
#include <util.h>
#include "stm32f411xe.h"                // CMSIS Device Specific header file

/**
 * @defgroup CPU Declarations
 * @brief 
 * @{
 */

/* Processor Clock rate */
#define SYS_CLK_RATE			16000000UL

/* Peripherals Clock rate */
#define APB2_CLK_RATE			SYS_CLK_RATE	

/** @} */

/**
 * @defgroup GPIO Peripheral Declarations
 * @brief 
 * @{
 */

/**
 * @brief Aliases GPIO ports
 * 
 * GPIO ports can be expressed using these aliases
 */
enum {
        PA = 0,
        PB,
        PC,
        PD,
        PE,
        PH = 7
};

/**
 * @brief Provides a type to hold the alias of GPIO alternate function.
 * 
 * Alternate functions can be expressed using these aliases
 */
enum {
	AF0, AF1, AF2, AF3, 
	AF4, AF5, AF6, AF7, 
	AF8, AF9, AF10, AF11, 
	AF12, AF13, AF14, AF15
};

/* Offset to GPIO base address */
#define GPIO_OFFSET	                (0x400UL)

/**
 * @breif GPIO register pointer
 *
 * This macro returns a pointer to the base address of the GPIO registers for a given port.
 *
 * @param x GPIO port identifier.
 * @return A pointer to the struct gpio for the corresponding GPIO port.
 */
#define GPIO(x)	                        (GPIO_TypeDef *)(AHB1PERIPH_BASE + GPIO_OFFSET * x)

/** @} */

/**
 * @defgroup USART Peripheral Declarations
 * @brief 
 * @{
 */

/** @} */

/**
 * @defgroup TIM Peripheral Declarations
 * @brief 
 * @{
 */

 #define TIM_CLK_RATE	                1000000UL // 1MHz Clock Rate for preconfigured APIs

/** @} */
/**
 * @defgroup ADC Peripheral Declarations
 * @brief 
 * @{
 */

#define ADC_RESOLUTION	                4095

/** @} */



#endif /* _STM32F411RE_H_ */
