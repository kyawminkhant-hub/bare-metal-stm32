#include <stm32f411re.h>

/* SysTick config helper Macro */
#define SYST_CSR_CONFIG(ENABLE, TICKINT, CLKSRC) \
        (ENABLE << 0) | (TICKINT << 1) | (CLKSRC << 2)

void systick_timer_configure(uint8_t enable, uint8_t tickint, uint8_t clksrc)
{
        SYST->CSR = SYST_CSR_CONFIG(enable, tickint, clksrc);
}

void systick_timer_set(uint32_t ticks)
{
        /* Load number of clock cycles per second */
        SYST->RVR = ticks - 1;

        /* Clear CVR Register */
        SYST->CVR = 0;
}

void ms_delay(uint32_t ms) 
{	
	/* Enalbe SysTick, and User internal clock */    
	systick_timer_configure(1, 0, 1);

	/* Set timer for 1ms */
	systick_timer_set(SYS_CLK_RATE / 1000);

	for (uint32_t i = 0; i < ms; i++) {
        	while ((SYST->CSR & SYST_CSR_CFLAG) == 0) {}
    	}
	
	systick_timer_configure(0, 0, 1);
}
