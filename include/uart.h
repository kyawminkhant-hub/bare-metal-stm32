#ifndef	UART_H
#define UART_H

#include <stdio.h>
#include <stm32f411re.h>

/* 
 * UART APIs
 */
void uart_configure(struct usart *uart, unsigned long baudrate);
void uart_write(struct usart *uart, char c);

#endif /* UART_H */
