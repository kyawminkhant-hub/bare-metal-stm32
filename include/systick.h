#ifndef	SYSTICK_H
#define SYSTICK_H

#include <stm32f411re.h>

/* SysTick helper Macros */
#define SYST_CSR_CONFIG(ENABLE, TICKINT, CLKSRC) \
        (ENABLE << 0) | (TICKINT << 1) | (CLKSRC << 2)

/*
 * SysTick APIs
 */
void systick_timer_configure(uint8_t enable, uint8_t tickint, uint8_t clksrc);
void systick_timer_set(uint32_t ticks); 
void delay_ms(uint32_t ms);

#endif
