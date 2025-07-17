#include <stdint.h>
#include <stdio.h>
#include <stm32f411re.h>

int main(void)
{
	uart_configure(USART1, 115200);

	while(1) {
		uart_write(USART1, "Hello world from STM32...\r\n");
		ms_delay(1000);
	}

	return 0;
}
