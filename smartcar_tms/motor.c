#include "motor.h"
#include "LCD12864.h"
#include "delay.h"
#include "uart.h"
u8 speed_level[3] = {50, 75, 95}, speed_idx = 1;
//0ֹͣ, 1ǰ��, 2����, 3��ת, 4��ת;
u8 run_flag = 0, last_run_flag = 0, obstacle = 0;

//��ʼ��
void MT_Init(void)
{
	P2M0 = 0;P2M1 = 0;
	IN2 = 1;
	IN4 = 1;
	P_SW2 |= BIT7;
	PWMCKS = 0;
	PWMCFG = 0;
	//��������
	PWMC = CYCLE;

	//˫·ռ�ձ�
	PWM6CR = 0;
	PWM6T1 = 0;
	PWM6T2 = CYCLE * DUTY / 100;
	PWM7CR = 0;
	PWM7T1 = 0;
	PWM7T2 = CYCLE * DUTY / 100;

	//ʹ��PWM���
	PWMCR = BIT4 + BIT5;               
	PWMCR |= ENPWM;
	P_SW2 &= ~BIT7;

	//ֹͣ
	MT_Stop();
}

//����С���ٶ�
void MT_SetSpeed(u8 wide)
{
	u8 wide1, wide2;
	if(run_flag > 0 && wide > 0)
	{
		switch(run_flag)
		{
			case 1:
				wide1 = 100 - wide;
				wide2 = 100 - wide;
				break;
			case 2:
				wide1 = wide;
				wide2 = wide;
				break;
			case 3:
				wide1 = wide;
				wide2 = 100 - wide;
				break;
			case 4:
				wide1 = 100 - wide;
				wide2 = wide;
				break;
			default: return;		
		}
		P_SW2 |= BIT7;
		PWM6T2 = (u16)(CYCLE * wide1 / 100);
		PWM7T2 = (u16)(CYCLE * wide2 / 100);
		P_SW2 &= ~BIT7;
		PWMCR |= BIT4+BIT5;
	}
	else
	{
		PWMCR &= ~(BIT4+BIT5);
		IN1 = 0;
		IN2 = 0;
		IN3 = 0;
		IN4 = 0;
	}	
}

//�ı��ٶȵȼ�
void MT_ChangeSpeed(void)
{
	u8 pStr[16] = "Speed Level:   ";
	speed_idx = (speed_idx + 1) % 3;
	pStr[13] = speed_idx + 1 + '0';
	LCD12864_DisplayString(0,4,"�ٶȸı�");
	UART1_SendString("ChangeSpeed\n");
}

//ǰ��
void MT_Forward(void)
{
	run_flag = 1;
	IN2 = 1;
	IN4 = 1;
	obstacle = 0;
	MT_Start();
		UART1_SendString("Forward\n");
	LCD12864_DisplayString(0,3,"С��ǰ��");	
	//PutString(0,0,"STATUS:Backward ");
}

//����
void MT_Backward(void)
{
	run_flag = 2;
	IN2 = 0;
	IN4 = 0;
	obstacle = 0;
	MT_Start();
	UART1_SendString("Backward\n");
	LCD12864_DisplayString(0,3,"С������ ");
//	PutString(0,0,"STATUS:Forward ");
}

//��ת
void MT_TurnLeft(void)
{
	run_flag = 3;
	IN2 = 0;
	IN4 = 1;
	obstacle = 0;
	MT_Start();
	UART1_SendString("TurnLeft\n");
	LCD12864_DisplayString(0,3,"С����ת ");		
//	PutString(0,0,"STATUS:TurnLeft ");
}

//��ת
void MT_TurnRight(void)
{
	run_flag = 4;
	IN2 = 1;
	IN4 = 0;
	obstacle = 0;
	MT_Start();
	UART1_SendString("TurnRight\n");
	LCD12864_DisplayString(0,3,"С����ת");
	//PutString(0,0,"STATUS:TurnRight");
}

//С��ֹͣ
void MT_Stop(void)
{
	 run_flag = 0;
	MT_SetSpeed(0);
	UART1_SendString("Stop\n");
	LCD12864_DisplayString(0,3,"С��ֹͣ");
//	PutString(0,0,"STATUS:Stop     ");
}

//С������
void MT_Start(void)
{
	MT_SetSpeed(speed_level[speed_idx]);
}

//�����ϰ���
void MT_Handle_Obstacle(void)
{	
	if(run_flag > 0 )
	{
		IN2 = 1;
		IN4 = 0;
		obstacle = 0;
		MT_Start();
		UART1_SendString("TurnRight\n");
		LCD12864_DisplayString(0,3,"С������");
	//	MT_TurnRight();
	}
}

//����û���ϰ���
void MT_Handle_NoObstacle(void)
{
	if(1)
	{
	//	obstacle = 0;
		//�ָ�ԭ����ʻ״̬
		switch(run_flag)
		{
			case 1: MT_Forward(); break;
			case 2: MT_Backward(); break;
			case 3: MT_TurnLeft(); break;
			case 4: MT_TurnRight(); break;
			default: break;
		}
	}
}