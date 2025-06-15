#ifndef	SYSTICK_H
#define SYSTICK_H

#include <stm32f411re.h>

#define SYST 			((struct systick *)0xE000E010)

#define SYST_CSR_ENABLE		(1U << 0)
#define SYST_CSR_TICKINT	(1U << 1)
#define SYST_CSR_CLKSRC		(1U << 2)
#define SYST_CSR_CFLAG		(1U << 16)

struct systick {
	volatile uint32_t CSR;
	volatile uint32_t RVR;
	volatile uint32_t CVR;
	volatile uint32_t CALIB;
};

/*
 * SysTick APIs
 */
void systick_timer_configure(uint8_t enable, uint8_t tickint, uint8_t clksrc);

void systick_timer_set(uint32_t ticks); 

void ms_delay(uint32_t ms);

#endif
