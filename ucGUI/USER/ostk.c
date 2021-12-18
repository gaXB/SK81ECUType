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
#include "LISTVIEW.h"


#define  uint8  unsigned char 
#define  uint16 unsigned short
#define	uint32	unsigned	long	

#define  int8   signed char
#define  int16  signed short
#define	int32		signed long
   
WM_HWIN CreateFramewin(void);
/*********************************************************************
*
*       Public code
*
**********************************************************************/


#define  MAX_ID_NUM      100
#define  EVENT_NUM    10
typedef struct
{
	uint16 id;
	uint8 u8Data[8];
}CANDATA;

CANDATA  sEventData[EVENT_NUM]=
{
	{0x1, 0x11, 0x11, 0x12, 0x77, 0x99, 0xaa, 0xee,0xff},
	{0x112, 0x11, 0x11, 0x12, 0x77, 0x99, 0xaa, 0xee,0xff},
	{0x112, 0x99, 0x88, 0x77, 0x66, 0x99, 0xaa, 0xee,0x11},
	{0x512, 0x11, 0x11, 0x12},
	{0x513, 0x12, 0x12, 0x12},
	{0x554, 0x11, 0x11, 0x12},
	{0x764, 0x11, 0x11, 0x12},
	{0x124, 0x12, 0x12, 0x12},
};
CANDATA  sCANBuffData[MAX_ID_NUM];
uint32  u32BuffDataTimes[MAX_ID_NUM];
static uint8 bIDBuffOver;
static unsigned int  u32IdTypeNumber;
static uint8 u8ECUType, bNotiFState;

WM_HWIN pListHand;

 extern  int      bFlash;

void Init_List(void)
{
	uint8 u8Line;
	uint16 i;
	u8Line = LISTVIEW_GetNumRows(pListHand);
	for (i = u8Line; i > 0; i--)
	{
		LISTVIEW_DeleteRow(pListHand, i);
	}
	LISTVIEW_DeleteRow(pListHand, 0);

	for (i = 0; i < u32IdTypeNumber; i++)
	{
		sCANBuffData[i].id = 0;
		u32BuffDataTimes[i] = 0;
	}
	GUI_Delay(100);
	u8Line = LISTVIEW_GetNumRows(pListHand);
	u32IdTypeNumber = 0;
}
void List_DisplayLine(uint8 u8Line)
{
	char str[10];
	uint8 i;
	sprintf(str, "0x%x", sCANBuffData[u8Line].id); //将100转为16进制表示的字符串。
	LISTVIEW_SetItemText(pListHand, 0, u8Line,str);

	sprintf(str, "%d", u32BuffDataTimes[u8Line]); //将100转为16进制表示的字符串。
	LISTVIEW_SetItemText(pListHand, 1, u8Line,str);

	for (i =0; i < 8; i++)
	{
		sprintf(str, "0x%x", sCANBuffData[u8Line].u8Data[i]); //将100转为16进制表示的字符串。
		LISTVIEW_SetItemText(pListHand, i+2, u8Line,str);
	}
	//LISTVIEW_SetSel(pListHand, u8Line);
}

void RecOneFram( CANDATA  *pRecData)
{
	uint16 i;

	for (i = 0; i < u32IdTypeNumber && pRecData->id != sCANBuffData[i].id ; i++)
	{//找到在那个位置	
	}

	if (i == u32IdTypeNumber)
	{//不存在的ID
		if (u32IdTypeNumber >= MAX_ID_NUM)
		{
			bIDBuffOver = 1;
		}
		else
		{//存入数据
			sCANBuffData[i] = *pRecData;
			u32IdTypeNumber++;
			if (u32IdTypeNumber > LISTVIEW_GetNumRows(pListHand))
			{
				LISTVIEW_AddRow(pListHand, NULL);
			}
			u32BuffDataTimes[i]++;

			List_DisplayLine(i);
		}
	}
	else
	{
		sCANBuffData[i] = *pRecData;
		u32BuffDataTimes[i]++;
		List_DisplayLine(i);
	}
}
int GUI_Exec(void);
WM_HWIN CreateCANDiag(void);
void emwindemo_task(void)
{
  static uint8 u8SendTimes = 0xff;
 //  static uint8 *p = (uint8*)(0);
   char abc[10];

  WM_HWIN hWin; 
   abc[0] = 48;
  GUI_CURSOR_Show();
	//更换皮肤
//	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
//	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
//	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
//	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
//	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
//	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
//	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
//	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
//	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
//	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
//	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
//	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
  GUI_SetBkColor(GUI_BLACK);
 // WM_SetCreateFlags(WM_CF_MEMDEV);
  hWin = CreateCANDiag();
//*p = 0;

 /// pListHand = WM_GetDialogItem(hWin, GUI_ID_USER + 0x01);
	while(1)
	{
      GUI_Delay(100);
      GUI_Exec();
      u8SendTimes++;
      if (u8SendTimes >= EVENT_NUM) 
      {
         u8SendTimes = 0;
         sEventData[0].id++;
         if (bNotiFState)
         GUI_MessageBox("Test Error The ECU type is Wrong.\n Check your Setting or Program", "ERROR", 0);
          WM_CreateTimer(WM_GetClientWindow(hWin), 0, 100, 0);
           if (bFlash)
           {
              bFlash = 0;
           }
           else
           {
              bFlash = 1;
           }
         //  WM_Paint(WM_GetClientWindow(hWin));
      }
      
   //   RecOneFram(&sEventData[u8SendTimes]);
	}
} 

/*********************************************************************
*
*       MainTask
*/

int MAN_SetType(void)
{
	u8ECUType++;
	if (u8ECUType >= 8)
	{
		u8ECUType = 0;
	}

	return u8ECUType;
}

int  MAN_SetNotiF(void)
{
	if (bNotiFState)
	{
		bNotiFState = 0;
	}
	else
	{
		bNotiFState = 1;
	}
	return bNotiFState;
}

