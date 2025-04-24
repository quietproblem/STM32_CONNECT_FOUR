#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_
#include "stm32f4xx_hal.h"
#include "InterruptControl.h"
#include <stdlib.h>
#include <stdbool.h>
#define BUTTON_PORT_VALUE GPIOA
#define BUTTON_PIN_NUMBER GPIO_PIN_NUM_0
#define BUTTON_PRESSED 1
#define BUTTON_UNPRESSED 0

void buttonInit();
bool buttonPressed();
void buttonInitInterrupt();



#endif /* BUTTON_DRIVER_H_ */
