#ifndef _MOTOR_H
#define _MOTOR_H
#include "intrins.h"
#include<STC15W4K58S4.H>
//IN1,IN3接PWM,IN2，IN4接普通IO即可
sbit IN1 = P1^6;	//IN1->P1.6
sbit IN2 = P1^4;	//IN2->P1.4
sbit IN3 = P1^7;	//IN3->P1.7
sbit IN4 = P1^5;	//IN4->P1.5

#define PWM6 IN1
#define PWM7 IN3

#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)
#define CYCLE 0x1000L
#define DUTY 25L
#define ENPWM 0x80

void MT_Init(void);
void MT_SetSpeed(u8 wide);
void MT_ChangeSpeed(void);
void MT_Stop(void);
void MT_Start(void);
void MT_Backward(void);
void MT_Forward(void);
void MT_TurnLeft(void);
void MT_TurnRight(void);
void MT_Handle_Obstacle(void);
void MT_Handle_NoObstacle(void);


#endif