#ifndef	UART_H
#define UART_H

#include <stdio.h>
#include <stm32f411re.h>
#include <gpio.h>
#include <ring_buffer.h>

/* External pointer for redirecting printf */
extern struct usart *uart_ptr;

/*
 * UART Interrupt Callback Functions
 */
typedef void (*uart_callback_t)(struct usart *uart);

static uart_callback_t uart1_callback;
static uart_callback_t uart2_callback;
static uart_callback_t uart6_callback;

/* UART Interrupt Flags */
typedef enum {
	UART_INT_TXE,
	UART_INT_CTS,
	UART_INT_TC,
	UART_INT_RXNE,
	UART_INT_IDLE,
	UART_INT_PE,
	UART_INT_LBD,
	UART_INT_ERR
} uart_irq_flag_t;

/* 
 * UART APIs
 */
void uart_configure(struct usart *uart, unsigned long baudrate);

void uart_write(struct usart *uart, char c);

static inline uint8_t uart_read_ready(struct usart *uart) {
        return uart->SR & USART_SR_RXNE;
}

static inline uint8_t uart_read(struct usart *uart) {
	return (uint8_t) (uart->DR & 255);
}

void uart_irq_enable(struct usart *uart, uart_irq_flag_t flag);

void uart_irq_callback_set(struct usart *uart, uart_callback_t callback);

#endif /* UART_H */
