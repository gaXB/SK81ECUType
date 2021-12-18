#include "sys.h"
#include "usart.h"		
#include "delay.h"
#include "math.h"
#include "stdio.h"
	
#include "led.h" 
#include "timer.h"

#include "gui.h"
#include "touch.h"

#include "WM.h"
#include "button.h"
#include "progbar.h"
#include "CHECKBOX.h"
#include "listbox.h"
#include "framewin.h"
#include "SCROLLBAR.h"
#include "edit.h"




// -------------------- 结构变量 --------------------- //
GUI_PID_STATE STATE;		//该变量为GUI触屏的x y位置存储坐标（内部已将其换算为屏幕坐标了）

FRAMEWIN_Handle hFrame;
WM_HWIN CreateFramewin(void);
WM_HWIN CreateCANDiag(void);
void emwindemo_task(void);
//
int main(void)
{		 			  
	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化  
	LED_Init();
			 
	GUI_Init();
	StartTouch();

//	GUI_SetBkColor(GUI_WHITE);
//	GUI_SetColor(GUI_BLACK);
//	GUI_Clear();
	GUI_SetFont(&GUI_Font8x16);

	Timerx_Init(71,1000);	
   WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
   emwindemo_task();
   
   
//	Frame_Init();
//	Edit_Init();
//	GUI_DispStringAt("2014/5/25", 160, 300);

//	while(1)
//	{			
//		Touch_Process();
//		Button_Process();

//	//	GUI_DispStringAt("Var", 0, 300);	
//	//	GUI_DispFloatFix(Variable, 9,3);
//	//	GUI_DispStringAt("Res", 120, 300);
//	//	GUI_DispFloatFix(Result, 9,3);

//	//	GUI_DispStringAt("Int:", 100, 300);
//	//	GUI_DispDec(Inte_Digits, 1);
//	//	GUI_DispStringAt("Dec:", 150, 300);
//	//	GUI_DispDec(Deci_Digits, 1);

//		GUI_Delay(10);			
//	}
}

























