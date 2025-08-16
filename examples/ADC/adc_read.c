#include <stm32f411re.h>
#include <gpio.h>
#include <uart.h>
#include <systick.h>
#include <adc.h>
#include <pwm.h>

int main(void) {

	uart_configure(USART1, 115200);

	/* Configure GPIO pin as analog mode: ADC1_4 */
	uint16_t A2 = GPIO_INIT(PA, 4);
	gpio_pin_configure(A2, GPIO_MODE_ANALOG);

	uint16_t LED = GPIO_INIT(PB, 4);	
	gpio_pin_configure(LED, GPIO_MODE_AF);
	gpio_pin_af_configure(LED, AF2); 
	
	adc_configure(ADC1, 4, ADC_MODE_CONT);

	int freq = 1000;
	int pot = 0;
	int percent = 0;

	while (1) {
		pot = adc_get(ADC1);
		percent = adc_get_percent(ADC1);
		
		pwm_set (TIM3, 1, percent, freq);

		printf("Pot Value: %d (%d%%) \r\n", pot, percent);
		delay_ms(1000);
	}
}

