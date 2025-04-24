#ifndef INTERRUPT_CONTROL_H_
#define INTERRUPT_CONTROL_H_
#include <stdint.h>
#include "stm32f4xx_hal.h"


#define EXTI0_IRQ_NUMBER 6
#define TIM2_IRQ_NUMBER 28
#define APB2_Base_ADDR 0x40010000
#define EXTI_Base_ADDR (APB2_Base_ADDR + 0x3C00) //this could be wrong
//#define EXTI ((EXTI_Reg_Def*)EXTI_Base_ADDR)


#define NVIC_ISER0 ((volatile uint32_t*) 0xE000E100)
#define NVIC_ICER0 ((volatile uint32_t*) 0XE000E180)
#define NVIC_ICPR0 ((volatile uint32_t*) 0XE000E280)



void enableIRQInterrupt(uint8_t IRQ_NUMBER);

void disableIRQInterrupt(uint8_t IRQ_NUMBER);

void clearIRQPendingInterrupt(uint8_t IRQ_NUMBER);

void setIRQPendingIterrupt(uint8_t IRQ_NUMBER);

void clearEXTIPendingInterrupt(uint8_t PIN_NUMBER);

#endif
