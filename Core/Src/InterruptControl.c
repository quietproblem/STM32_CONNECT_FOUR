#include "InterruptControl.h"

void enableIRQInterrupt(uint8_t IRQ_NUMBER)
{
	if(IRQ_NUMBER<32)
	{
		*NVIC_ISER0=(1<<IRQ_NUMBER);
	}
}

void disableIRQInterrupt(uint8_t IRQ_NUMBER)
{
	if(IRQ_NUMBER<32)
	{
		*NVIC_ISER0=(1<<IRQ_NUMBER);
	}
}

void clearIRQPendingInterrupt(uint8_t IRQ_NUMBER)
{
	if(IRQ_NUMBER<32)
	{
		*NVIC_ISER0=(1<<IRQ_NUMBER);
	}
}


void clearEXTIPendingInterrupt(uint8_t PIN_NUMBER)
{
	EXTI->PR|=(1<<PIN_NUMBER);

}




