#include <stm32f411re.h>
#include <gpio.h>
#include <uart.h>
#include <ring_buffer.h>

#define UART_BUFFER_SIZE (16)

struct usart *uart_ptr;

static uint8_t buffer[UART_BUFFER_SIZE];
static struct ring_buffer tx_buffer = { .buffer = buffer, .size = sizeof(buffer) };

void uart_configure(struct usart *uart, unsigned long baudrate)
{
	uint16_t tx_pin = 0, rx_pin = 0;

	uart_ptr = uart;

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
	uart->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

}

void uart_write(struct usart *uart, char ch) 
{
	while (ring_buffer_full(&tx_buffer));

	ring_buffer_set(&tx_buffer, ch);	
	
	/* Enable TXE interrupt */
	NVIC_EnableIRQ(USART1_IRQn);
	uart->CR1 |= USART_SR_TXE;
}

void USART1_IRQHandler(void)
{	
	if (ring_buffer_empty(&tx_buffer)) {
		USART1->CR1 &= ~(1U << 7); // disable TXE interrupt when buffer is empty
		return;
	}

	uint8_t ch = ring_buffer_get(&tx_buffer); 
		
	if (USART1->SR & USART_SR_TXE)
		USART1->DR = ch; 
}
