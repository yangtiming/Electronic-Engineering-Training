#ifndef _LCD12864_H
#define _LCD12864_H

#include <STC15W4K58S4.H>

#define Busy    0x80 //���ڼ��LCD״̬���е�Busy��ʶ
/***************************���Ŷ���***************************/
#define LCD_Data P0	  //���ݶ˿�
sbit LCD_RS = P2^0;	  //����Ĵ���ѡ��
sbit LCD_RW = P2^1;	  //��дѡ��
sbit LCD_EN = P2^2;	  //ʹ�ܿ���
sbit LCD_PSB = P2^3;	//������ʽѡ��
sbit LCD_RST = P2^4;	//��λ�˿�

void	LCD12864_WriteData(unsigned char dat);
void	LCD12864_WriteCmd(unsigned char dat,busy_flag);
unsigned char	LCD12864_ReadStatus(void);
void	LCD12864_Init(void);
void	LCD12864_Clear(void);
void	LCD12864_DisplayString(unsigned char X, unsigned char Y, unsigned char code *dat);
void	LCD12864_DisplayImg (unsigned char code *dat);

#endif
