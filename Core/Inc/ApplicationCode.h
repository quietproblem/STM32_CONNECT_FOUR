/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */




#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

#include "LCD_Driver.h"
#include "Button_Driver.h"
#include "stm32f4xx_hal.h"
#include "Scheduler.h"

#include <stdio.h>

#define MAX_MOVES 42
#define WIN 1
#define NOT_FINISHED 0
#define TIE 2
#define BOARD_ROWS 6
#define BOARD_COLUMNS 7
#define EXTI0 0
void ApplicationInit(void);
void game_init();
void displayTime();
void LCD_Visual_Demo(void);
void LCD_PrintBoard();
void update_game_board();
bool onePlayerMode();
//#if (COMPILE_TOUCH_FUNCTIONS == 1)
void LCD_Touch_Polling_Demo(void);
void LCD_Touch_Player_Count(void);
int LCD_Touch_Move_Chip();
int check_for_win();
bool getGameState();
void resetGame();
//#endif // (COMPILE_TOUCH_FUNCTIONS == 1)

#endif /* INC_APPLICATIONCODE_H_ */
