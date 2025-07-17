#include <stm32f411re.h>

void uart_configure(struct usart *uart, unsigned long baudrate)
{
	uint16_t tx_pin = 0, rx_pin = 0;

	if (uart == USART1) {
		RCC->APB2ENR |= USART1EN;
		tx_pin = GPIO_INIT(GPIOA, 9);
		rx_pin = GPIO_INIT(GPIOA, 9);
	}

	if (uart == USART6) {
		RCC->APB2ENR |= USART6EN;
		tx_pin = GPIO_INIT(GPIOC, 6);
		rx_pin = GPIO_INIT(GPIOC, 7);
	}

	if (uart == USART2) {
		RCC->APB1ENR |= USART2EN;
		tx_pin = GPIO_INIT(GPIOA, 2);
		rx_pin = GPIO_INIT(GPIOA, 3);
	}
	
	gpio_pin_configure(tx_pin, GPIO_MODE_AF);
	gpio_pin_af_configure(tx_pin, AF7);

	gpio_pin_configure(rx_pin, GPIO_MODE_AF);
	gpio_pin_af_configure(rx_pin, AF7);

	uart->BRR =  ((SYS_CLK_RATE + (baudrate / 2U)) / baudrate);
	uart->CR1 |= (USART_CR1_TE | USART_CR1_UE);
}

unsigned long uart_write(struct usart *uart, char* buf)
{
	unsigned long bytes = 0;

	while (*buf) {
		while (!(uart->SR & USART_SR_TXE)) {}
		uart->DR = *(uint8_t *) buf;
		buf++; 
		bytes++;
	}

	return bytes;
}
