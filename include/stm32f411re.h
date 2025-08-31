#ifndef STM32F411RE_H
#define STM32F411RE_H

#include <stdint.h>
#include <stdio.h>

/*
 * Peripheral Registers Structures
 */

/* General Purpose Timers */
struct tim {
	volatile uint32_t CR1;         // Offset: 0x00 
	volatile uint32_t CR2;         // Offset: 0x04 
	volatile uint32_t SMCR;        // Offset: 0x08 
	volatile uint32_t DIER;        // Offset: 0x0C 
	volatile uint32_t SR;          // Offset: 0x10 
	volatile uint32_t EGR;         // Offset: 0x14 
	volatile uint32_t CCMR1;       // Offset: 0x18 
	volatile uint32_t CCMR2;       // Offset: 0x1C 
	volatile uint32_t CCER;        // Offset: 0x20 
	volatile uint32_t CNT;         // Offset: 0x24 
	volatile uint32_t PSC;         // Offset: 0x28 
	volatile uint32_t ARR;         // Offset: 0x2C 
	volatile uint32_t RCR;         // Offset: 0x30 
	volatile uint32_t CCR1;        // Offset: 0x34 
	volatile uint32_t CCR2;        // Offset: 0x38 
	volatile uint32_t CCR3;        // Offset: 0x3C 
	volatile uint32_t CCR4;        // Offset: 0x40 
	volatile uint32_t BDTR;        // Offset: 0x44 
	volatile uint32_t DCR;         // Offset: 0x48 
	volatile uint32_t DMAR;        // Offset: 0x4C 
	volatile uint32_t OR;          // Offset: 0x50 
};

/* GPIO */
struct gpio {
	volatile uint32_t MODER;    	// Offset 0x00
	volatile uint32_t OTYPER;   	// Offset 0x04
	volatile uint32_t OSPEEDR;  	// Offset 0x08
    	volatile uint32_t PUPDR;    	// Offset 0x0C
    	volatile uint32_t IDR;      	// Offset 0x10
    	volatile uint32_t ODR;      	// Offset 0x14
    	volatile uint32_t BSRR;     	// Offset 0x18
    	volatile uint32_t LCKR;     	// Offset 0x1C
    	volatile uint32_t AFR[2];   	// Offset 0x20 and 0x24
};

/* ADC */
struct adc {
	volatile uint32_t SR;     /* Offset: 0x00 */
	volatile uint32_t CR1;    /* Offset: 0x04 */
	volatile uint32_t CR2;    /* Offset: 0x08 */
	volatile uint32_t SMPR1;  /* Offset: 0x0C */
	volatile uint32_t SMPR2;  /* Offset: 0x10 */
	volatile uint32_t JOFR1;  /* Offset: 0x14 */
	volatile uint32_t JOFR2;  /* Offset: 0x18 */
	volatile uint32_t JOFR3;  /* Offset: 0x1C */
	volatile uint32_t JOFR4;  /* Offset: 0x20 */
	volatile uint32_t HTR;    /* Offset: 0x24 */
	volatile uint32_t LTR;    /* Offset: 0x28 */
	volatile uint32_t SQR1;   /* Offset: 0x2C */
	volatile uint32_t SQR2;   /* Offset: 0x30 */
	volatile uint32_t SQR3;   /* Offset: 0x34 */
	volatile uint32_t JSQR;   /* Offset: 0x38*/
	volatile uint32_t JDR1;   /* Offset: 0x3C */
	volatile uint32_t JDR2;   /* Offset: 0x40 */
	volatile uint32_t JDR3;   /* Offset: 0x44 */
	volatile uint32_t JDR4;   /* Offset: 0x48 */
	volatile uint32_t DR;     /* Offset: 0x4C */
};

/* SysTick */
struct systick {
	volatile uint32_t CSR;
	volatile uint32_t RVR;
	volatile uint32_t CVR;
	volatile uint32_t CALIB;
};

/* RCC */ 
struct rcc {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t RESERVED0[2];
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t RESERVED2[2];
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED3[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t RESERVED4[2];
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED5[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED6[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t RESERVED7;
	volatile uint32_t DCKCFGR;
};

/* USART */
struct usart {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
};

/*
 * Peripheral Register Addresses
 */

/* Peripheral Base Address */
#define PERIPH_BASE				(0x40000000UL)

/* APB1 Bus Addresses */
#define APB1PERIPH_BASE				PERIPH_BASE

/* APB2 Bus Addresses */
#define APB2PERIPH_OFFSET			(0x00010000UL)
#define APB2PERIPH_BASE				(PERIPH_BASE + APB2PERIPH_OFFSET)

/* AHB1 Bus Addresses */
#define AHB1PERIPH_OFFSET			(0x00020000UL)
#define AHB1PERIPH_BASE				(PERIPH_BASE + AHB1PERIPH_OFFSET)

/* Cortex-M4 Internal Peripherals */

/* SysTIck */
#define SYST_BASE				(0xE000E010UL)

/* RCC */
#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

/* GPIO */
#define GPIO_OFFSET                             (0x400UL)

#define GPIOA_BASE				(AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE				(AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE				(AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE				(AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE				(AHB1PERIPH_BASE + 0x1000UL)
#define GPIOH_BASE				(AHB1PERIPH_BASE + 0x1C00UL)

/* General-purpose Timers (TIM2 to TIM5) */ 
#define TIM2_BASE				(APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE				(APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE				(APB1PERIPH_BASE + 0x0800UL)
#define TIM5_BASE				(APB1PERIPH_BASE + 0x0C00UL)

/* USART */
#define USART1_BASE				(0x40011000UL)
#define USART6_BASE				(0x40011400UL)
#define USART2_BASE				(0x40004400UL)

/* ADC */
#define ADC1_BASE				(APB2PERIPH_BASE + 0x2000UL)

/*
 * Peripheral Declarations
 */

/* Processor Clock rate */
#define SYS_CLK_RATE				16000000UL

/* Peripherals Clock rate */
#define APB2_CLK_RATE				SYS_CLK_RATE	

/* SysTick */
#define SYST					((struct systick *) SYST_BASE)
#define SYST_CSR_ENABLE				(1U << 0)
#define SYST_CSR_TICKINT			(1U << 1)
#define SYST_CSR_CLKSRC				(1U << 2)
#define SYST_CSR_CFLAG				(1U << 16)

/* RCC */
#define RCC					((struct rcc *) RCC_BASE)
#define RCC_APB2ENR_SYSCFGEN			(1U << 14)

/* GPIO */
#define GPIOA					((struct gpio *) GPIOA_BASE)
#define GPIOB					((struct gpio *) GPIOB_BASE)
#define GPIOC					((struct gpio *) GPIOC_BASE)
#define GPIOD					((struct gpio *) GPIOD_BASE)
#define GPIOE					((struct gpio *) GPIOE_BASE)
#define GPIOH					((struct gpio *) GPIOH_BASE)

/* General-purpose Timers (TIM2 to TIM5) */
#define TIM2					((struct tim *) TIM2_BASE)
#define TIM3					((struct tim *) TIM3_BASE)
#define TIM4					((struct tim *) TIM4_BASE)
#define TIM5					((struct tim *) TIM5_BASE)

#define NVIC_ISER0 				((volatile uint32_t*) 0xE000E100)

#define TIM2EN					(1U << 0)
#define TIM3EN					(1U << 1)
#define TIM4EN					(1U << 2)
#define TIM5EN					(1U << 3)

#define TIM_CCER_CC1E				(1U << 0)
#define TIM_CCER_CC2E				(1U << 4)
#define TIM_CCER_CC3E				(1U << 8)
#define TIM_CCER_CC4E				(1U << 12)

#define TIM_CR1_CEN				(1U << 0)
#define TIM_CR1_ARPE				(1U << 7)
#define TIM_DIER_UIE				(1U << 0)
#define TIM_SR_UIF				(1U << 0)
#define TIM_EGR_UG				(1U << 0)

#define TIM2_IRQn				28
#define TIM3_IRQn				29
#define TIM4_IRQn				30
#define TIM5_IRQn				50

/* USART */
#define USART1					((struct usart *) USART1_BASE)
#define USART2					((struct usart *) USART2_BASE)
#define USART6					((struct usart *) USART6_BASE)

#define USART1EN				(1U << 4)
#define USART6EN				(1U << 5)
#define USART2EN				(1U << 17)

#define USART1_IRQn				37
#define USART2_IRQn				38
#define USART6_IRQn				71

#define USART_CR1_RE				(1U << 2)
#define USART_CR1_TE				(1U << 3)
#define USART_CR1_UE				(1U << 13)

#define USART_SR_TXE				(1U << 7)
#define USART_SR_RXNE				(1U << 5)

/* ADC */
#define ADC1					((struct adc *) ADC1_BASE)

#define ADC1EN					(1U << 8)
#define ADC_CR2_ADON				(1U << 0)
#define ADC_CR2_CONT				(1U << 1)
#define ADC_CR2_SWSTART				(1U << 30)
#define ADC_SR_EOC				(1U << 1)

/*
 * NVIC
 */

static inline void NVIC_EnableIRQ(uint8_t irq_num) {
	NVIC_ISER0[irq_num >> 5] = (1U << (irq_num & 0x1F));
}

#endif /* STM32F411RE_H */
