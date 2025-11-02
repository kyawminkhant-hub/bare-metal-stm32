#include <hal.h>

#define LED 		PINMAP(PB, 4)
#define A2			PINMAP(PA, 4)

#define USART1_TX	PINMUX(PA, 9, AF7)
#define USART1_RX	PINMUX(PA, 10, AF7)

struct uart_config console_cfg = {
	.tx_pin = USART1_TX,
	.rx_pin = USART1_RX,
	.baudrate = 115200
};

int main(void) {

	int freq = 1000;
	int pot = 0;
	int percent = 0;

	uart_configure(USART1, &console_cfg);

	/* Configure GPIO pin PA4 as analog mode: ADC1_4 */
	gpio_pin_configure(A2, GPIO_MODE_ANALOG);

	/* Configure GPIO pin as PWM (AF2 - TIM3_CH1) */
	gpio_pin_configure(LED, GPIO_MODE_AF);
	gpio_pin_af_configure(LED, AF2); 
	
	adc_configure(ADC1, 4, ADC_MODE_CONT);

	while (1) {
		pot = adc_get(ADC1);
		percent = adc_get_percent(ADC1);
		
		pwm_set(TIM3, 1, percent, freq);

		printf("Pot Value: %d (%d%%) \r\n", pot, percent);
		delay_ms(1000);
	}

	return 0;
}

