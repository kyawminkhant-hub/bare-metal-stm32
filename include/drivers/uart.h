#ifndef	_UART_H_
#define _UART_H_

#include <stdio.h>
#include <string.h>
#include "stm32f411xe.h"	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>
#include <ring_buffer.h>

/* Typedef for UART interrupt callback functions */
typedef void (*uart_callback_t)(USART_TypeDef *usart);

/**
 * @brief struct for USART peripheral configurations
 *
 * This struct instance is used to represent configuarations
 * for each USART peripheral
 * 
 * @param tx_pin Pinmux for Transmit
 * @param rx_pin Pinmux for Recevie
 * @param baudrate Communication baud rate
 */
struct uart_config {
	uint32_t tx_pin;
	uint32_t rx_pin;
	uint32_t baudrate;
};

struct uart_driver_data {
	uart_callback_t callback;
	struct ring_buffer tx_buffer;
	struct ring_buffer rx_buffer;
};

/* USART Interrupt Request Flags */
typedef enum {
	UART_IRQ_TXE,
	UART_IRQ_CTS,
	UART_IRQ_TC,
	UART_IRQ_RXNE,
	UART_IRQ_IDLE,
	UART_IRQ_PE,
	UART_IRQ_LBD,
	UART_IRQ_ERR
} uart_irq_flag_t;

/* UART Driver APIs */
static inline void usart_rcc_enable(USART_TypeDef *usart) {	
	if (usart == USART1)
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	if (usart == USART2)
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	if (usart == USART6)
		RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
}

void uart_configure(USART_TypeDef *usart, struct uart_config *cfg);

static inline bool uart_read_ready(USART_TypeDef *usart) {
	return usart->SR & USART_SR_RXNE;
}

static inline uint8_t uart_read(USART_TypeDef *usart) {
	return (uint8_t) (usart->DR & 255);
}

static inline void uart_write(USART_TypeDef *usart, uint8_t byte) {
  	while (!(usart->SR & USART_SR_TXE));
  	usart->DR = byte;
}

void uart_irq_enable(USART_TypeDef *usart, uart_irq_flag_t flag);
void uart_irq_callback_set(USART_TypeDef *usart, uart_callback_t callback);

#ifdef UART_INTERRUPT_DRIVEN
void uart_irq_write(USART_TypeDef *usart, char c);
int uart_irq_read(USART_TypeDef *usart);
#endif

#endif /* _UART_H_ */
