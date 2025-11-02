#ifndef	_SYSTICK_H_
#define _SYSTICK_H_

#include <stdio.h>
#include <string.h>
#include "stm32f411xe.h"	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>

struct systick_config {
        uint8_t enable; 
        uint8_t tickint;
        uint8_t clksource;
        uint32_t ticks;
};

/* SysTick APIs */
static inline void systick_configure(struct systick_config *cfg) {
	SysTick->CTRL = (cfg->enable << 0) | (cfg->tickint<< 1) | (cfg->clksource << 2);

        /* Load number of clock cycles per second */
	SysTick->LOAD = cfg->ticks - 1;

	/* Clear VAL Register */
	SysTick->VAL = 0;
}

void delay_ms(uint32_t ms) 
{	
        struct systick_config systick_cfg;
	
        /* Enable Systick Counter */  
        systick_cfg.enable = 1;

        /* Use Processor Internal Clock */  
        systick_cfg.clksource = 1;

        /* Disable SysTick exception request */
        systick_cfg.tickint = 0;

	/* Set timer for 1ms */
	systick_cfg.ticks = (SYS_CLK_RATE / 1000);

        systick_configure(&systick_cfg);

        /* Counting */
	for (uint32_t i = 0; i < ms; i++) {
        	while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
	}
	
        /* Disable Systick Counter */
        systick_cfg.enable = 0;
	systick_configure(&systick_cfg);
}

#endif /* _SYSTICK_H_ */
