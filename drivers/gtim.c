#include <stdio.h>
#include "stm32f411xe.h" 	// CMSIS Device Specific
#include <stm32f411re.h>	// Board Specs Declarations
#include <hal_conf.h>
#include <gtim.h>

#define GTIM_DRIVER_INIT(index)																\
    static struct gtim_driver_data gtim##index##_driver_data = {							\
		.callback = NULL            														\
    };																						\
																							\
	void TIM##index##_IRQHandler(void) {													\
    	if (gtim##index##_driver_data.callback) {											\
        	gtim##index##_driver_data.callback(TIM##index);									\
    	}																					\
	}		

#define FOREACH_TIM(M)																		\
    M(2) 																					\
    M(3)																					\
    M(4)																					\
	M(5)																					

FOREACH_TIM(GTIM_DRIVER_INIT)

void gtim_irq_enable(TIM_TypeDef *gtim, gtim_irq_flag_t flag) 
{	
	/* Enable NVIC IRQ */
	if (gtim == TIM2)
		NVIC_EnableIRQ(TIM2_IRQn);
	else if (gtim == TIM3)
		NVIC_EnableIRQ(TIM3_IRQn);	
	else if (gtim == TIM4)
		NVIC_EnableIRQ(TIM4_IRQn);	
	else if (gtim == TIM5)
		NVIC_EnableIRQ(TIM5_IRQn);	

	/* Enable corresponding TIM Interrupt */
	switch (flag) {
	case TIM_INT_UIF:
		gtim->DIER |= TIM_DIER_UIE;
		break;
	case TIM_INT_CC1F:
		gtim->DIER |= TIM_DIER_CC1IE;
		break;
	case TIM_INT_CC2F:
		gtim->DIER |= TIM_DIER_CC2IE;
		break;
	case TIM_INT_CC3F:
		gtim->DIER |= TIM_DIER_CC3IE;
		break;
	case TIM_INT_CC4F:
		gtim->DIER |= TIM_DIER_CC4IE;
		break;
	case TIM_INT_TIF:
		gtim->DIER |= TIM_DIER_TIE;
		break;
	default:
		break;
	}
}

void gtim_irq_callback_set(TIM_TypeDef *gtim, gtim_callback_t callback)
{
	/* Add callback functions to corresponding TIM ISR */
	if (gtim == TIM2) 
		gtim2_driver_data.callback = callback;
	else if (gtim == TIM3)
		gtim3_driver_data.callback = callback;
	else if (gtim == TIM4)
		gtim4_driver_data.callback = callback;
	else if (gtim == TIM5)
		gtim5_driver_data.callback = callback;
}