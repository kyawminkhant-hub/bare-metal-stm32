#ifndef	UART_H
#define UART_H

#include <stm32f411re.h>

#define USART1		((struct usart *) USART1_BASE)
#define USART6		((struct usart *) USART6_BASE)
#define USART2		((struct usart *) USART2_BASE)

#define USART1EN	(1U << 4)
#define USART6EN	(1U << 5)
#define USART2EN	(1U << 17)

#define USART_CR1_TE	(1U << 3)
#define USART_CR1_UE	(1U << 13)
#define USART_SR_TXE	(1U << 7)

struct usart {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
};

void uart_configure(struct usart *uart, unsigned long baudrate);
unsigned long uart_write(struct usart *uart, char* buf);

#endif
