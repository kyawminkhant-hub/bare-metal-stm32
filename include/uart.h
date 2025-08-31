#ifndef	UART_H
#define UART_H

#include <stdio.h>
#include <stm32f411re.h>

extern struct usart *uart_ptr;

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

#endif /* UART_H */
