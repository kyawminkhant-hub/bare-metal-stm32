#include <stm32f411re.h>
#include <uart.h>
#include <systick.h>

int main(void) {
	uart_configure(USART1, 115200);
	int count = 0;

	while (1) {
		printf("[%d] Hello World \r\n", count);
		count++;
		delay_ms(1000);
	}
}

