#include <stdio.h>
#include "stm32f411xe.h" 	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>
#include <ring_buffer.h>
#include <gpio.h>
#include <util.h>
#include <uart.h>

static void uart_fifo_callback(USART_TypeDef *usart);

#ifdef UART_INTERRUPT_DRIVEN
#define UART_CALLBACK_INIT .callback = uart_fifo_callback,
#else
#define UART_CALLBACK_INIT .callback = NULL,
#endif

#define UART_DRIVER_INIT(index)																\
    static uint8_t uart##index##_tx_buffer[UART_FIFO_BUFFER_SIZE];							\
	static uint8_t uart##index##_rx_buffer[UART_FIFO_BUFFER_SIZE];							\
    static struct uart_driver_data uart##index##_driver_data = {							\
		UART_CALLBACK_INIT																	\
        .tx_buffer = {                                           							\
            .buffer = uart##index##_tx_buffer,                     							\
            .size = sizeof(uart##index##_tx_buffer),	             						\
			.write_index = 0,																\
			.read_index = 0																	\
        },																					\
		.rx_buffer = {                                           							\
            .buffer = uart##index##_rx_buffer,                     							\
            .size = sizeof(uart##index##_rx_buffer),	             						\
			.write_index = 0,																\
			.read_index = 0																	\
        }																					\
    };																						\
																							\
	void USART##index##_IRQHandler(void) {													\
    	if (uart##index##_driver_data.callback) {											\
        	uart##index##_driver_data.callback(USART##index);								\
    	}																					\
	}		

#define FOREACH_USART(M)																	\
    M(1) 																					\
    M(2)																					\
    M(6)											

FOREACH_USART(UART_DRIVER_INIT)

void uart_configure(USART_TypeDef *usart, struct uart_config *cfg)
{	
	/* Enable RCC Clock access to USART */
	usart_rcc_enable(usart);

	/* Configure TX and RX pins as alternate function */
	gpio_pin_configure(PORT(cfg->tx_pin), PIN(cfg->tx_pin), GPIO_MODE_AF);
	gpio_pin_af_configure(PORT(cfg->tx_pin), PIN(cfg->tx_pin), AF(cfg->tx_pin));

	gpio_pin_configure(PORT(cfg->rx_pin), PIN(cfg->rx_pin), GPIO_MODE_AF);
	gpio_pin_af_configure(PORT(cfg->rx_pin), PIN(cfg->rx_pin), AF(cfg->rx_pin));
	
	/* Configure Baudrate */
	usart->BRR =  ((SYS_CLK_RATE + (cfg->baudrate / 2U)) / cfg->baudrate);
	
	/* Enable USART */
	usart->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

#ifdef UART_INTERRUPT_DRIVEN
	/* Enable RXNE interrupt before receiving any data */
	uart_irq_enable(usart, UART_IRQ_RXNE);
#endif

}

void uart_irq_write(USART_TypeDef *usart, char ch) 
{	
	struct uart_driver_data *data = NULL;

	if (usart == USART1)
		data = &uart1_driver_data;
	else if (usart == USART2)
		data = &uart2_driver_data;
	else if (usart == USART6)
		data = &uart6_driver_data;
    
	/*
	if (!data) {
        return -1;   // invalid usart
    }
	*/
	
	if (!ring_buffer_full(&data->tx_buffer)) 
		ring_buffer_put(&data->tx_buffer, ch);
	
	/* Enable TXE interrupt only if it’s currently disabled */
	if ((usart->CR1 & USART_CR1_TXEIE) == 0)
		uart_irq_enable(usart, UART_IRQ_TXE);
	
	/* return 0 // on sucess */
}

int uart_irq_read(USART_TypeDef *usart) 
{
	struct uart_driver_data *data = NULL;

	if (usart == USART1)
	    data = &uart1_driver_data;
	else if (usart == USART2)
	    data = &uart2_driver_data;
	else if (usart == USART6)
	    data = &uart6_driver_data;
	    
	/*
	if (!data) {
	    return -1;   // invalid usart
	}
	*/

	if (!ring_buffer_empty(&data->rx_buffer)) 
    	return ring_buffer_get(&data->rx_buffer);

	return -1; /* if buffer is empty */
}

void uart_irq_enable(USART_TypeDef *usart, uart_irq_flag_t flag)
{	
	/* Enable NVIC IRQ */
	if (usart == USART1)
		NVIC_EnableIRQ(USART1_IRQn);
	else if (usart == USART2)
		NVIC_EnableIRQ(USART2_IRQn);
	else if (usart == USART6)
		NVIC_EnableIRQ(USART6_IRQn);
	
	/* Enable corresponding UART Interrupt */
	switch (flag) {
	case UART_IRQ_TXE:
		usart->CR1 |= USART_CR1_TXEIE; 
		break;
	case UART_IRQ_CTS:
		usart->CR3 |= USART_CR3_CTSIE;
		break;
	case UART_IRQ_TC:
		usart->CR1 |= USART_CR1_TCIE; 
		break;
	case UART_IRQ_RXNE:
		usart->CR1 |= USART_CR1_RXNEIE;
		break;
	case UART_IRQ_IDLE:
		usart->CR1 |= USART_CR1_IDLEIE;
		break;
	case UART_IRQ_PE:
		usart->CR1 |= USART_CR1_PEIE; 
		break;
	case UART_IRQ_LBD:
		usart->CR2 |= USART_CR2_LBDIE; 
		break;
	case UART_IRQ_ERR:
		usart->CR3 |= USART_CR3_EIE;
		break;
	default:
		break;
	}
}

void uart_irq_callback_set(USART_TypeDef *usart, uart_callback_t callback)
{
	/* Add callback functions to the corresponding USART ISR */
	if (usart == USART1)
		uart1_driver_data.callback = callback;
	else if (usart == USART2)
		uart2_driver_data.callback = callback;
	else if (usart == USART6)
		uart6_driver_data.callback = callback;
}

static void uart_fifo_callback(USART_TypeDef *usart)
{
	struct uart_driver_data *data = NULL;

	if (usart == USART1)
	    data = &uart1_driver_data;
	else if (usart == USART2)
	    data = &uart2_driver_data;
	else if (usart == USART6)
	    data = &uart6_driver_data;

	/* FIFO TX handling */
	if (usart->SR & USART_SR_TXE) {
	    
		if (!ring_buffer_empty(&data->tx_buffer)) {
			uint8_t ch = ring_buffer_get(&data->tx_buffer);
			usart->DR = ch;
		} else {
			usart->CR1 &= ~USART_CR1_TXEIE; // clear TXE interrupt when buffer is empty
		}	
	}

	/* FIFO RX handling */
	if (usart->SR & USART_SR_RXNE) {
	    uint8_t ch = usart->DR & 0xFF;	// auto clear RXNE interrupt whenever DR is read 

	    if (!ring_buffer_full(&data->rx_buffer))
			ring_buffer_put(&data->rx_buffer, ch);
	}
}
