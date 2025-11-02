#include <hal.h>

#define USART1_TX	PINMUX(PA, 9, AF7)
#define USART1_RX	PINMUX(PA, 10, AF7)

struct uart_config cfg = {
	.tx_pin = USART1_TX,
	.rx_pin = USART1_RX,
	.baudrate = 115200
};

int main(void) 
{	
	char ch;
	uart_configure(USART1, &cfg);
	
	while (1) {

		// Polling 
		if (uart_read_ready(USART1)) {
			ch = uart_read(USART1);
			printf("echo \'%c\' \r\n", ch);
		}
	}
	
	return 0;
}

