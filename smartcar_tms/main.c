#include <STC15W4K58S4.H>
#include "Delay.h"
#include "uart.h"
#include "LCD12864.h"
#include "motor.h"
#include "sonic.h"
#include "infrared.h"

unsigned char code display1[] = {"����С��"};
unsigned char code display2[] = {"TM&BW&JC"};
void main()
{
	u16 sr_dis;

	//�˿ڳ�ʼ������׼ģʽ
    P5M0 = 0;
	P5M1 = 0;
    P0M0 = 0;
	P0M1 = 0;
    P1M0 = 0;
	P1M1 = 0;
    P2M0 = 0;
	P2M1 = 0;

    UART_Init();	//��������ռ��P3.0 P3.1
	Delay_Nms(100);
	//���PWM�˿ڳ�ʼ��
    MT_Init();		//���ռ��P1.4-P1.7
	Delay_Nms(100);
	LCD12864_Init(); //LCM��ʼ��
	//LCD��ʾ
	LCD12864_Clear();
	LCD12864_DisplayString(0,1,display1);	//��ʾ�ֿ��е���������
	LCD12864_DisplayString(0,2,display2);		//��ʾ�ֿ��е���������

//	Delay_Nms(10000);
//	UART1_SendString("STATUS:Stop\n");

	//���ڳ�ʼ��
	Delay_Nms(100);
	//���PWM�˿ڳ�ʼ��
  // MT_Init();		//���ռ��P1.4-P1.7
	//������ģ���ʼ��
	SR_Init();		//������ռ��P3.4 P3.5
//	IR_Init();		//ѭ�����⴫������P4.1��D0��P4.2��A0���������ã�




	//��ѭ��
	while(1)
	{
		//Delay_Nms(100);
		//���ʹ����ź�
		Delay_Nms(1000);
		SR_SendTrig();   
		//��ʱ200ms
	//	Delay1ms();
		Delay_200ms();
		//��ȡ��ǰ���������룬��λ cm
		sr_dis = SR_GetDis();
		if(sr_dis <= 30)
		{  	//LCD12864_DisplayString(0,4,"ok");		//��ʾ�ֿ��е���������
			UART1_SendString("STATUS:obstacle");
			//MT_TurnRight();
			MT_Handle_Obstacle();
		}
		else
		{
			MT_Handle_NoObstacle();
		}
  	}
}