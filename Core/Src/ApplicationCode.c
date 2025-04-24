/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"


typedef struct
{
	int row;
	int column;
}pair;
typedef struct
{
	int player_cnt;
	int board[6][7];
	int column_count[7] ;
	int player;
	pair last_drop;
	int current_position;
	int remaining_moves;
	int old_time;
	int end_time;
}Game;
Game game;


extern void initialise_monitor_handles(void);

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
	buttonInitInterrupt();
	LTCD__Init();
	LTCD_Layer_Init(0);
	LCD_Clear(0,LCD_COLOR_WHITE);

#if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

#endif // COMPILE_TOUCH_FUNCTIONS
}

void displayTime()
{

}


void game_init()
{
	for(int i=0; i<BOARD_COLUMNS;i++)
	{
		for(int j=0; j<BOARD_ROWS; j++)
		{
			game.board[i][j]=0;
		}
	}
	game.remaining_moves=MAX_MOVES;
	game.player_cnt=-1;
}
void update_game_board()
{

	int column_position=game.current_position;
	if(game.column_count[column_position]+1>6)
	{
		return;
	}
	game.remaining_moves--;
	game.column_count[column_position]++;
	int current_row_pos=5;
	while(game.board[current_row_pos][column_position]!=0)
	{
		current_row_pos--;
	}
	game.board[current_row_pos][column_position]=game.player;
	game.last_drop.row=current_row_pos;
	game.last_drop.column=column_position;
	game.current_position=0;

	if(game.player==1)
	{
		game.player=2;
	}

	else if(game.player==2)
	{
		game.player=1;
	}


	return;
}

int check_for_win()
{

	int old_player;

	if(game.player==1)
	{
		old_player=2;
	}

	if(game.player==2)
	{
		old_player=1;
	}
	if(game.remaining_moves==0)
	{
		return TIE;
	}
	int current_count=1;
	int current_row=game.last_drop.row;
	int current_col=game.last_drop.column;
	//work up until different color or boundary

	while(current_row-1>=0&&game.board[current_row-1][current_col]==old_player)
	{
		current_count++;
		current_row--;
	}

	//reset back to original starting location
	current_row=game.last_drop.row;
	current_col=game.last_drop.column;
	while(current_row+1<=5&&game.board[current_row+1][current_col]==old_player)
	{
		current_count++;
		current_row++;
	}

	//WIN
	if(current_count>=4)
	{
		return WIN;
	}

	current_row=game.last_drop.row;
	current_col=game.last_drop.column;
	current_count=1;

	while(current_col-1>=0&&game.board[current_row][current_col-1]==old_player)
	{
		current_count++;
		current_col--;
	}
	current_row=game.last_drop.row;
	current_col=game.last_drop.column;

	while(current_col+1<=6&&game.board[current_row][current_col+1]==old_player)
	{
		current_count++;
		current_col++;
	}

	if(current_count>=4)
	{
		return WIN;
	}

	current_row=game.last_drop.row;
	current_col=game.last_drop.column;
	current_count=1;

	while(current_col-1>=0 && current_row-1>=0 &&game.board[current_row-1][current_col-1]==old_player)
	{
		current_count++;
		current_col--;
		current_row--;
	}

	current_row=game.last_drop.row;
	current_col=game.last_drop.column;

	while(current_col+1<=6 &&current_row+1<=5 &&game.board[current_row+1][current_col+1]==old_player)
	{
		current_count++;
		current_col++;
		current_row++;
	}

	if(current_count>=4)
	{
		return WIN;
	}


	current_row=game.last_drop.row;
	current_col=game.last_drop.column;
	current_count=1;

	while(current_col+1>=6 && current_row-1>=0 &&game.board[current_row-1][current_col+1]==old_player)
	{
		current_count++;

		current_col++;
		current_row--;
	}

	current_row=game.last_drop.row;
	current_col=game.last_drop.column;

	while(current_col-1>=0 &&current_row+1<=5 &&game.board[current_row+1][current_col-1]==old_player)
	{
		current_count++;

		current_col--;
		current_row++;
	}

	if(current_count>=4)
	{
		return WIN;
	}

	//work left until different color or boundary
	//work right until different color or boundary

	//work left and up until different color or boundary
	//work right and down until different color or boundary

	//work right and up until different color or boundary
	//work left and down until different color or boundary

	return NOT_FINISHED;
}
void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1

int LCD_Touch_Move_Chip()
{
//	LCD_Clear(0,LCD_COLOR_WHITE);
	LCD_Print_Chip(game.current_position,game.player);
		if ((returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) ){
			/* Touch valid */
			HAL_Delay(250);
//			LCD_Clear(0,LCD_COLOR_WHITE);
			if(StaticTouchData.x<=120)
			{
				if(game.current_position-1>=0)
				{
					game.current_position--;
				}
				LCD_Clear(0,LCD_COLOR_WHITE);
				LCD_Print_Chip(game.current_position,game.player);
				return 1;
			}

			else if(StaticTouchData.x>120)
			{
				if((game.current_position+1<=6))
				{
					game.current_position++;
				}
				LCD_Clear(0,LCD_COLOR_WHITE);
				LCD_Print_Chip(game.current_position,game.player);
				return 1;
			}

		}
	return 0;
}

void EXTI0_IRQHandler()
{
	disableIRQInterrupt(EXTI0_IRQn);
	//clearIRQPendingInterrupt(GPIO_PIN_0);
	clearIRQPendingInterrupt(EXTI0_IRQn);
	clearEXTIPendingInterrupt(EXTI0);
	addScheduleEvent(DROP_CHIP_EVENT);
	enableIRQInterrupt(EXTI0_IRQn);
}


void LCD_Touch_Player_Count(void)
{
	LCD_Clear(0,LCD_COLOR_BLUE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);

	LCD_DisplayChar(40,140,'1');
	LCD_DisplayChar(180,140,'2');

	while(game.player_cnt==-1)
	{
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			if(StaticTouchData.x<=120)
			{
				game.player_cnt=1;
				game.player=1;
			}

			else
			{
				game.player_cnt=2;
				game.player=1;
			}
		}
	}
	LCD_Clear(0,LCD_COLOR_WHITE);
	return;
}

void LCD_PrintBoard()
{
	LCD_Clear(0,LCD_COLOR_WHITE);
	for(int i=80;i<320;i+=40)
	{
		LCD_Draw_Horizontal_Line(0,i,240,LCD_COLOR_BLACK);
	}

	for(int i=0;i<240;i+=35)
	{
		LCD_Draw_Vertical_Line(i,80,250,LCD_COLOR_BLACK);
	}
	for(int j=0;j<7;j++)
	{
		for(int i=0;i<6;i++)
		{
			int x_pos=(35*j)+17;
			int y_pos=(40*i)+100; //was sixty
			if(game.board[i][j]==1)
			{
				LCD_Draw_Circle_Fill(x_pos,y_pos,10,LCD_COLOR_YELLOW);
			}



			else if(game.board[i][j]==2)
			{
				LCD_Draw_Circle_Fill(x_pos,y_pos,10,LCD_COLOR_RED);
			}
		}
	}
	return;
}



//void LCD_Touch_Polling_Demo(void)
//{
//	LCD_Clear(0,LCD_COLOR_GREEN);
//	while (1) {
//		/* If touch pressed */
//		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
//			/* Touch valid */
////			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
//			if(StaticTouchData.x<=120)
//			{
//				LCD_Clear(0, LCD_COLOR_RED);
//			}
//
//			else
//			{
//				LCD_Clear(0, LCD_COLOR_BLUE);
//			}
//
//
//
//		} else {
//			/* Touch not pressed */
//			printf("Not Pressed\n\n");
//			LCD_Clear(0, LCD_COLOR_GREEN);
//		}
//	}
//}
//return -1;
//}



#endif // COMPILE_TOUCH_FUNCTIONS

