#include <stm32f411re.h>
#include <gpio.h>
#include <uart.h>

void uart_configure(struct usart *uart, unsigned long baudrate)
{
	uint16_t tx_pin = 0, rx_pin = 0;

	if (uart == USART1) {
		RCC->APB2ENR |= USART1EN;
		tx_pin = GPIO_INIT(PA, 9);
		rx_pin = GPIO_INIT(PA, 10);
	}

	if (uart == USART6) {
		RCC->APB2ENR |= USART6EN;
		tx_pin = GPIO_INIT(PC, 6);
		rx_pin = GPIO_INIT(PC, 7);
	}

	if (uart == USART2) {
		RCC->APB1ENR |= USART2EN;
		tx_pin = GPIO_INIT(PA, 2);
		rx_pin = GPIO_INIT(PA, 3);
	}
	
	gpio_pin_configure(tx_pin, GPIO_MODE_AF);
	gpio_pin_af_configure(tx_pin, AF7);

	gpio_pin_configure(rx_pin, GPIO_MODE_AF);
	gpio_pin_af_configure(rx_pin, AF7);

	uart->BRR =  ((SYS_CLK_RATE + (baudrate / 2U)) / baudrate);
	uart->CR1 |= (USART_CR1_TE | USART_CR1_UE);
}

void uart_write(struct usart *uart, char ch) 
{
	while (!(uart->SR & USART_SR_TXE)) {}
    	uart->DR = (uint8_t) ch;
}
