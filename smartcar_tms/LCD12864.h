#ifndef _LCD12864_H
#define _LCD12864_H

#include <STC15W4K58S4.H>

#define Busy    0x80 //用于检测LCD状态字中的Busy标识
/***************************引脚定义***************************/
#define LCD_Data P0	  //数据端口
sbit LCD_RS = P2^0;	  //输入寄存器选择
sbit LCD_RW = P2^1;	  //读写选择
sbit LCD_EN = P2^2;	  //使能控制
sbit LCD_PSB = P2^3;	//串并方式选择
sbit LCD_RST = P2^4;	//复位端口

void	LCD12864_WriteData(unsigned char dat);
void	LCD12864_WriteCmd(unsigned char dat,busy_flag);
unsigned char	LCD12864_ReadStatus(void);
void	LCD12864_Init(void);
void	LCD12864_Clear(void);
void	LCD12864_DisplayString(unsigned char X, unsigned char Y, unsigned char code *dat);
void	LCD12864_DisplayImg (unsigned char code *dat);

#endif
