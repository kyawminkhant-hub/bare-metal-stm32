#include <stm32f411re.h>
#include <uart.h>
#include <systick.h>

int main(void) {
	uart_configure(USART1, 115200);
	uint8_t ch;

	while (1) {

		if (uart_read_ready(USART1))
		{
			ch = uart_read(USART1);
			printf("echo \'%c\' \r\n", ch);
		}
	}
}

