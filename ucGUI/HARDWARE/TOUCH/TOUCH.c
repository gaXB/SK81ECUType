#include"TOUCH.h"

void WriteComTouch(u8 com)
{
	u8 i,temp;
	
	DCLK=0;
	for (i=0;i<8;i++)
	{
		temp=com & 0x80;  //从最高位取Bit 
		if (temp==0)
		{
			DIN=0;
		}
		else
		{ 
			DIN=1;
		}
			com<<=1;
			DCLK=0;    //底电平放数上总线
			DCLK=1;    //上升沿后 ADS7843 读总线数据 
	}
}

u16 ReadDaTouch(void)
{
	u8 i;
	u16 data;
	
	delay_us(6);                   
	DCLK=1;                              
	DCLK=0; 
	for (i=0;i<16;i++)
	{
		data<<=1;
		DCLK=1;
		delay_us(1);
		DCLK=0;                        
		if (DOUT)data++;
	}
	data>>=4; 
	return (data);
}

void StartTouch(void)
{
	DCLK = 0;

	RCC->APB2ENR |= 1 << 4;
	GPIOC->CRL &= 0xffff0000;
	GPIOC->CRL |= 0x00003883;
	GPIOC->CRH &= 0xff0fffff;
	GPIOC->CRH |= 0x00300000;

	CS = 1;
	DIN = 1;
	DCLK = 1;
	CS = 0;							  
}

u8 ReadXYDataTouch(u16 *x, u16 *y, u8 flag)
{
	u16 x1, y1;
	u16 x2, y2;
	u16 xda, yda;

	//*******************		
	WriteComTouch(CMD_RDX);
	x1 = ReadDaTouch();
	WriteComTouch(CMD_RDY);
	y1 = ReadDaTouch();
	//*******************
	WriteComTouch(CMD_RDX);
	x2 = ReadDaTouch();
	WriteComTouch(CMD_RDY);
	y2 = ReadDaTouch();
	//********************
	if (x1 < x2)
		if((x2 - x1) > ERR_RANGE)
			return 1;
	else
		if(x1 - x2 > ERR_RANGE)
			return 1;

	if (y1 < y2)
		if(y2 - y1 > ERR_RANGE)
			return 1;
	else
		if(y[0] - y[1] > ERR_RANGE)
			return 1;
	//*********************
	if (flag == 1)
	{
		xda = (u16)((x2 + x1)/2.0);
		yda = (u16)((y2 + y1)/2.0);

		*x = (u16)((yda - 200)/(15.0));
		*y = (u16)((3900 - xda)/(11.0));
	}
	else
	{
		*x = (u16)((x2 + x1)/2.0);
		*y = (u16)((y2 + y1)/2.0);
	}
	return 0;
}

int Get_DValue(int da1, int da2)
{
	int DValue;

	if (da1 > da2)
	{
		DValue = (int)(da1 - da2);
	}
	else
	{
		DValue = (int)(da2 - da1);
	}
	return DValue;
}

//*******以下4个函数为GUI与触屏接口*******
void GUI_TOUCH_X_ActivateX(void)
{
	;//这两个函数没有用 但是编译需要
}

void GUI_TOUCH_X_ActivateY(void)
{
	;//这两个函数没有用 但是编译需要
}
//X轴转换过程处理  返回AD值
int GUI_TOUCH_X_MeasureX(void)
{
	static int save_ad=0;
	int ad = 0;
	int ad_test[3];
	u8 i=0;

	for(i=0;i<3;i++)
	{
		WriteComTouch(CMD_RDX);
		ad_test[i]=ReadDaTouch();
	}
	if (Get_DValue(ad_test[0], ad_test[1]) > ERR_RANGE || Get_DValue(ad_test[1], ad_test[2]) > ERR_RANGE)
		return save_ad;
	ad = (ad_test[0]+ad_test[1]+ad_test[2])/3;
	//****************消抖******************
	if (ad < save_ad)
	{
		if((save_ad - ad) <= ERR_RANGE)
			ad = save_ad;
	}
	else
	{
		if(ad - save_ad <= ERR_RANGE)
			ad = save_ad;
	}
	//***************************************
	save_ad = ad;
	return (ad);
}

//Y轴转换过程处理  返回AD值
int GUI_TOUCH_X_MeasureY(void)
{
	static int save_ad=0;
	int ad = 0;
	int ad_test[3];
	u8 i=0;

	for(i=0;i<3;i++)
	{
		WriteComTouch(CMD_RDY);
		ad_test[i]=ReadDaTouch();
	}
	if (Get_DValue(ad_test[0], ad_test[1]) > ERR_RANGE || Get_DValue(ad_test[1], ad_test[2]) > ERR_RANGE)
		return save_ad;
	ad = (ad_test[0]+ad_test[1]+ad_test[2])/3;
	//****************消抖******************
	if (ad < save_ad)
	{
		if((save_ad - ad) <= ERR_RANGE)
			ad = save_ad;
	}
	else
	{
		if(ad - save_ad <= ERR_RANGE)
			ad = save_ad;
	}
	//***************************************
	save_ad = ad;
	return (ad);
}
//****************************************************
