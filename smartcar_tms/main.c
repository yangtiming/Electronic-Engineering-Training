#include <STC15W4K58S4.H>
#include "Delay.h"
#include "uart.h"
#include "LCD12864.h"
#include "motor.h"
#include "sonic.h"
#include "infrared.h"

unsigned char code display1[] = {"智能小车"};
unsigned char code display2[] = {"TM&BW&JC"};
void main()
{
	u16 sr_dis;

	//端口初始化，标准模式
    P5M0 = 0;
	P5M1 = 0;
    P0M0 = 0;
	P0M1 = 0;
    P1M0 = 0;
	P1M1 = 0;
    P2M0 = 0;
	P2M1 = 0;

    UART_Init();	//串口蓝牙占用P3.0 P3.1
	Delay_Nms(100);
	//电机PWM端口初始化
    MT_Init();		//电机占用P1.4-P1.7
	Delay_Nms(100);
	LCD12864_Init(); //LCM初始化
	//LCD显示
	LCD12864_Clear();
	LCD12864_DisplayString(0,1,display1);	//显示字库中的中文数字
	LCD12864_DisplayString(0,2,display2);		//显示字库中的中文数字

//	Delay_Nms(10000);
//	UART1_SendString("STATUS:Stop\n");

	//串口初始化
	Delay_Nms(100);
	//电机PWM端口初始化
  // MT_Init();		//电机占用P1.4-P1.7
	//超声波模块初始化
	SR_Init();		//超声波占用P3.4 P3.5
//	IR_Init();		//循迹红外传感器，P4.1接D0，P4.2接A0（可能无用）




	//主循环
	while(1)
	{
		//Delay_Nms(100);
		//发送触发信号
		Delay_Nms(1000);
		SR_SendTrig();   
		//延时200ms
	//	Delay1ms();
		Delay_200ms();
		//获取当前超声波距离，单位 cm
		sr_dis = SR_GetDis();
		if(sr_dis <= 30)
		{  	//LCD12864_DisplayString(0,4,"ok");		//显示字库中的中文数字
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