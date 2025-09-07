#include <uart.h>

#define UART_FIFO_BUFFER_SIZE 16

struct usart *uart_ptr;

static uint8_t buffer[UART_FIFO_BUFFER_SIZE];
static struct ring_buffer tx_buffer = { .buffer = buffer, .size = sizeof(buffer) };

static void uart_fifo_tx_callback(struct usart *uart)
{
	if (ring_buffer_empty(&tx_buffer)) {
		uart->CR1 &= ~USART_CR1_TXIE; // disable TXE interrupt when buffer is empty
		return;
	}

	uint8_t ch = ring_buffer_get(&tx_buffer);

	if (uart->SR & USART_SR_TXE)
		uart->DR = ch;
}

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

	/* Add FIFO callback function */
	uart_irq_callback_set(uart, uart_fifo_tx_callback);

	/* Enable TXE interrupt */
	uart_irq_enable(uart, UART_INT_TXE);
}

void uart_irq_enable(struct usart *uart, uart_irq_flag_t flag)
{
	/* Enable NVIC IRQ */
	if (uart == USART1)
		NVIC_EnableIRQ(USART1_IRQn);
	else if (uart == USART2)
		NVIC_EnableIRQ(USART2_IRQn);
	else if (uart == USART6)
		NVIC_EnableIRQ(USART6_IRQn);

	/* Enable corresponding UART Interrupt */
	switch (flag) {
	case UART_INT_TXE:
		uart->CR1 |= USART_CR1_TXIE; 
		break;
	case UART_INT_CTS:
		uart->CR3 |= USART_CR3_CTSIE;
		break;
	case UART_INT_TC:
		uart->CR1 |= USART_CR1_TCIE; 
		break;
	case UART_INT_RXNE:
		uart->CR1 |= USART_CR1_RXNEIE;
		break;
	case UART_INT_IDLE:
		uart->CR1 |= USART_CR1_IDLEIE;
		break;
	case UART_INT_PE:
		uart->CR1 |= USART_CR1_PEIE; 
		break;
	case UART_INT_LBD:
		uart->CR2 |= USART_CR2_LBDIE; 
		break;
	case UART_INT_ERR:
		uart->CR3 |= USART_CR3_EIE;
		break;
	default:
		break;
	}
}

void uart_irq_callback_set(struct usart *uart, uart_callback_t callback)
{
	/* Add callback functions to the corresponding USART ISR */
	if (uart == USART1)
		uart1_callback = callback;
	else if (uart == USART2)
		uart2_callback = callback;
	else if (uart == USART6)
		uart6_callback = callback;
}

void USART1_IRQHandler(void) {	
	uart1_callback(USART1);
}

void USART2_IRQHandler(void) {	
	uart2_callback(USART2);
}

void USART6_IRQHandler(void) {	
	uart6_callback(USART6);
}
