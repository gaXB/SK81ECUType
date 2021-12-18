#ifndef __TOUCH_H
#define __TOUCH_H

#include"sys.h"
#include"delay.h"

//�봥���������������
#define PEN    PCin(1)   //PC1  INT
#define DOUT   PCin(2)   //PC2  MISO
#define DIN    PCout(3)  //PC3  MOSI
#define DCLK   PCout(0)  //PC0  SCLK
#define CS     PCout(13) //PC13 CS   
//***********************************
//ADS7843����ϵͳ��Ҫָ��
#define CMD_RDX     0X90  //0B10010000   ���ò�ַ�ʽ��X����
#define CMD_RDY     0XD0  //0B11010000  ���ò�ַ�ʽ��Y����
//************************************************************
#define ERR_RANGE	30	//�����������Χ

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
