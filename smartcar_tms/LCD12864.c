#include <STC15W4K58S4.H>
#include "Delay.h"
#include "uart.h"
#include "LCD12864.h"
#include "motor.h"
#include "sonic.h"
#include "infrared.h"

//******************************************
//д����
void LCD12864_WriteData(unsigned char dat)
{
	LCD12864_ReadStatus(); 		//���æ 
	LCD_RS = 1;								//д��ʱ��		
	LCD_RW = 0;
	LCD_Data = dat;

	Delay_Nms(10);
	LCD_EN = 1;
	Delay_Nms(10);
	LCD_EN = 0;
}

//дָ��
void LCD12864_WriteCmd(unsigned char dat,busy_flag) 
{
	if (busy_flag) 
		LCD12864_ReadStatus(); //���æ 
	LCD_RS = 0;
	LCD_RW = 0; 
	LCD_Data = dat;
	Delay_Nms(10);
	LCD_EN = 1; 
	Delay_Nms(10);
	LCD_EN = 0;  
}

//��״̬
unsigned char LCD12864_ReadStatus(void)
{
	LCD_Data = 0xFF; 
	LCD_RS = 0;
	LCD_RW = 1; 
	Delay_Nms(10);
	LCD_EN = 1;
	Delay_Nms(10);
	while (LCD_Data & Busy);//���æ�ź�
	LCD_EN = 0;
	return(LCD_Data);
}
//LCD��ʼ��
void LCD12864_Init(void) 
{
	LCD_PSB = 1;							 //����
	Delay_Nms(10);
	LCD_RST = 0;
	Delay_Nms(10);
	LCD_RST = 1;
	Delay_Nms(100);
	
	LCD12864_WriteCmd(0x30,1); //��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
	LCD12864_WriteCmd(0x01,1); //��ʾ����
	LCD12864_WriteCmd(0x06,1); // ��ʾ����ƶ�����
	LCD12864_WriteCmd(0x0C,1); // ��ʾ�����������
}

void LCD12864_Clear(void) //����
{
	LCD12864_WriteCmd(0x01,1); //��ʾ����
	LCD12864_WriteCmd(0x34,1); // ��ʾ����ƶ�����
	LCD12864_WriteCmd(0x30,1); // ��ʾ�����������
}


//��ָ��λ����ʾһ���ַ�
void LCD12864_DisplayString(unsigned char X, unsigned char Y, unsigned char code *dat)
{
	unsigned char ListLength,X2;
	ListLength = 0;
	X2 = X;
	if(Y < 1)	Y=1;					//����X������16
	if(Y > 4)	Y=4;					//YС��4
	X &= 0x0F; 
	switch(Y)
	{
		case 1: X2 |= 0X80;	break;	//����������ѡ����Ӧ��ַ
		case 2: X2 |= 0X90;	break;
		case 3: X2 |= 0X88;	break;
		case 4: X2 |= 0X98;	break;
	}
	LCD12864_WriteCmd(X2, 1); 			//���͵�ַ��
	while (dat[ListLength] >= 0x20) //�ַ�������
	{
		if (X <= 0x0F) 
		{
			LCD12864_WriteData(dat[ListLength]); 
			ListLength++;
			X++;
		}
	}
}

//ͼ����ʾ122*32
void LCD12864_DisplayImg (unsigned char code *dat)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	for(i=0;i<9;)												 //������������ʼ��ַ��ͬ
	{
		for(x=0;x<32;x++)									 //32��
		{
			LCD12864_WriteCmd(0x34,1);
			LCD12864_WriteCmd((0x80+x),1);	 //�е�ַ
			LCD12864_WriteCmd((0x80+i),1); 	 //�е�ַ
			LCD12864_WriteCmd(0x30,1);		
			for(y=0;y<16;y++)	
				LCD12864_WriteData(dat[tmp+y]);//��ȡ����д��LCD
			tmp+=16;		
		}
		i+=8;
	}
	LCD12864_WriteCmd(0x36,1);						//���书���趨
	LCD12864_WriteCmd(0x30,1);
}



