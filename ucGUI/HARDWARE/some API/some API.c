#include "gui.h"

static void cbBackgroudWin(WM_MESSAGE* pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_PAINT:GUI_Clear();
		default:
			WM_DefaultProc(pMsg);
	}
}

static void cbForegroundWin(WM_MESSAGE* pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_GREEN);
			GUI_Clear();
			GUI_DispString("ForeGround window");
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

static void DemoRedraw(void)
{
	GUI_HWIN hWnd;
	while(1)
	{
		hWnd = WM_CreateWindow(10,10,100,100,WM_CF_SHOW,cbForegroundWin,0);
		GUI_Delay(1000);
		
		WM_DeleteWindow(hWnd);
		GUI_DispStringAt("Background of window has not been redrawn",10,10);
		
		GUI_Delay(1000);
		GUI_Clear();
		
		WM_SetCallback(WM_HBKWIN,cbBackgroudWin);
		hWnd = WM_CreateWindow(10,10,100,100,WM_CF_SHOW,cbForegroundWin,0);
		GUI_Delay(1000);
		
		WM_DeleteWindow(hWnd);
		GUI_Delay(1000);
		
		WM_SetCallback(WM_HBKWIN,0);
	}
}

void Progbar(void)
{	
	GUI_DispStringAt("PROGRESS BAR",100,0);

	hBar = PROGBAR_Create(100,20,100,20,WM_CF_SHOW);
	PROGBAR_SetBarColor(hBar,0,GUI_BLUE);
	PROGBAR_SetBarColor(hBar,1,GUI_YELLOW);	
}
// ----------------------------------------------- //

// ----------------------------------------------- //
void Listbox(void)
{
	int i;
	int Entries = countof(table)-1;
	LISTBOX_Handle hlist;
	int ySize = GUI_GetYSizeOfFont(&GUI_Font13B_1)*Entries;
	hlist = LISTBOX_Create(table,10,10,60,ySize,WM_CF_SHOW);
	SCROLLBAR_CreateAttached(hlist,SCROLLBAR_CF_VERTICAL);
	for(i=0;i<Entries-1;i++)
	{
	//	delay_ms(500);
		LISTBOX_IncSel(hlist);
		WM_Exec();
	}
	for(i=0;i<Entries-1;i++)
	{
	//	delay_ms(500);
		LISTBOX_DecSel(hlist);
		WM_Exec();
	}

}
//

//
void Button_Init(void)
{
{hButton=BUTTON_Create(10,100,40,20,GUI_ID_OK,WM_CF_SHOW);//创建一个按钮
	hbut1=BUTTON_Create(10,120,40,20,2,WM_CF_SHOW);//创建一个按钮
	hbut2=BUTTON_C(eate(10,140,40,20,3,WM_CF_SHOW);ABLE):一个按钮
}

   BUTTON_SetText(hButton, "Click");
	BUTTON_SetText(hbut1, "Click");
	BUTTON_SetText(hbut2, "Click");
}
//

//
void MessageBox(void)
{
	WM_SetBkWindowColor(GUI_WHITE);
	GUI_MessageBox("aa","bb",GUI_MESSAGEBOX_CF_MOVEABLE);
}


