#ifndef _HAL_CONF_H_
#define _HAL_CONF_H_

/* Include app configuration first */
#include "config.h"

/**
 * @defgroup UART HAL Config 
 * @brief UART HAL configuration options & default values
 * @{
 */

#ifndef UART_INTERRUPT_DRIVEN
// #define UART_INTERRUPT_DRIVEN
#endif

#ifndef UART_CONSOLE
#define UART_CONSOLE		            USART2
#endif

#ifndef UART_FIFO_BUFFER_SIZE
#define UART_FIFO_BUFFER_SIZE           16
#endif

/** @} */

#endif /* _HAL_CONF_H_ */
