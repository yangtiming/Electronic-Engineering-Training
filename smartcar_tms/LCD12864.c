#include <STC15W4K58S4.H>
#include "Delay.h"
#include "uart.h"
#include "LCD12864.h"
#include "motor.h"
#include "sonic.h"
#include "infrared.h"

//******************************************
//写数据
void LCD12864_WriteData(unsigned char dat)
{
	LCD12864_ReadStatus(); 		//检测忙 
	LCD_RS = 1;								//写的时序		
	LCD_RW = 0;
	LCD_Data = dat;

	Delay_Nms(10);
	LCD_EN = 1;
	Delay_Nms(10);
	LCD_EN = 0;
}

//写指令
void LCD12864_WriteCmd(unsigned char dat,busy_flag) 
{
	if (busy_flag) 
		LCD12864_ReadStatus(); //检测忙 
	LCD_RS = 0;
	LCD_RW = 0; 
	LCD_Data = dat;
	Delay_Nms(10);
	LCD_EN = 1; 
	Delay_Nms(10);
	LCD_EN = 0;  
}

//读状态
unsigned char LCD12864_ReadStatus(void)
{
	LCD_Data = 0xFF; 
	LCD_RS = 0;
	LCD_RW = 1; 
	Delay_Nms(10);
	LCD_EN = 1;
	Delay_Nms(10);
	while (LCD_Data & Busy);//检测忙信号
	LCD_EN = 0;
	return(LCD_Data);
}
//LCD初始化
void LCD12864_Init(void) 
{
	LCD_PSB = 1;							 //并口
	Delay_Nms(10);
	LCD_RST = 0;
	Delay_Nms(10);
	LCD_RST = 1;
	Delay_Nms(100);
	
	LCD12864_WriteCmd(0x30,1); //显示模式设置,开始要求每次检测忙信号
	LCD12864_WriteCmd(0x01,1); //显示清屏
	LCD12864_WriteCmd(0x06,1); // 显示光标移动设置
	LCD12864_WriteCmd(0x0C,1); // 显示开及光标设置
}

void LCD12864_Clear(void) //清屏
{
	LCD12864_WriteCmd(0x01,1); //显示清屏
	LCD12864_WriteCmd(0x34,1); // 显示光标移动设置
	LCD12864_WriteCmd(0x30,1); // 显示开及光标设置
}


//按指定位置显示一串字符
void LCD12864_DisplayString(unsigned char X, unsigned char Y, unsigned char code *dat)
{
	unsigned char ListLength,X2;
	ListLength = 0;
	X2 = X;
	if(Y < 1)	Y=1;					//限制X不大于16
	if(Y > 4)	Y=4;					//Y小于4
	X &= 0x0F; 
	switch(Y)
	{
		case 1: X2 |= 0X80;	break;	//根据行数来选择相应地址
		case 2: X2 |= 0X90;	break;
		case 3: X2 |= 0X88;	break;
		case 4: X2 |= 0X98;	break;
	}
	LCD12864_WriteCmd(X2, 1); 			//发送地址码
	while (dat[ListLength] >= 0x20) //字符串结束
	{
		if (X <= 0x0F) 
		{
			LCD12864_WriteData(dat[ListLength]); 
			ListLength++;
			X++;
		}
	}
}

//图形显示122*32
void LCD12864_DisplayImg (unsigned char code *dat)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	for(i=0;i<9;)												 //分上下屏，起始地址不同
	{
		for(x=0;x<32;x++)									 //32行
		{
			LCD12864_WriteCmd(0x34,1);
			LCD12864_WriteCmd((0x80+x),1);	 //列地址
			LCD12864_WriteCmd((0x80+i),1); 	 //行地址
			LCD12864_WriteCmd(0x30,1);		
			for(y=0;y<16;y++)	
				LCD12864_WriteData(dat[tmp+y]);//读取数据写入LCD
			tmp+=16;		
		}
		i+=8;
	}
	LCD12864_WriteCmd(0x36,1);						//扩充功能设定
	LCD12864_WriteCmd(0x30,1);
}



