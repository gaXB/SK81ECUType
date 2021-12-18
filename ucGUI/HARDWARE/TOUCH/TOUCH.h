#ifndef __TOUCH_H
#define __TOUCH_H

#include"sys.h"
#include"delay.h"

//与触摸屏功能相关引脚
#define PEN    PCin(1)   //PC1  INT
#define DOUT   PCin(2)   //PC2  MISO
#define DIN    PCout(3)  //PC3  MOSI
#define DCLK   PCout(0)  //PC0  SCLK
#define CS     PCout(13) //PC13 CS   
//***********************************
//ADS7843命令系统重要指令
#define CMD_RDX     0X90  //0B10010000   即用差分方式读X坐标
#define CMD_RDY     0XD0  //0B11010000  即用差分方式读Y坐标
//************************************************************
#define ERR_RANGE	30	//读数误差允许范围

typedef struct gui_touch_pos
{
	unsigned int  x;
	unsigned int  y;
	unsigned char Ent;
}GUI_TOUCH_POS;

void WriteComTouch(u8 com);
u16 ReadDaTouch(void);
void StartTouch(void);
u8 ReadXYDataTouch(u16 *x, u16 *y, u8 flag);
void GUI_TOUCH_X_ActivateX(void);
void GUI_TOUCH_X_ActivateY(void);
int GUI_TOUCH_X_MeasureX(void);
int GUI_TOUCH_X_MeasureY(void);
int Get_DValue(int da1, int da2);

#endif
