#include"uart.h"
#include "LCD12864.h"
#include "motor.h"

//���ڳ�ʼ����9600bps@12MHz
void UART_Init(void)
{
	SCON = 0x50;
	AUXR |= 0x40;
	AUXR &= 0xFE;
	TMOD &= 0x0F;
	TL1 = 0xE0;
	TH1 = 0xFE;
	ET1 = 0;
	TR1 = 1;
	REN = 1;
	ES = 1;
}

//���ڷ���һ��char
void UART1_SendData(unsigned char dat)
{
	SBUF = dat;
	TI = 0;
	while(!TI);
}

//���ڷ����ַ���
void UART1_SendString(char *str)
{
	unsigned char idx = 0;
	while(*(str+idx)!='\0')
	{
		UART1_SendData(*(str+idx));
		idx++;
  	}

}

//����������
void Handle_UART_CMD(u8 cmd)
{
	switch(cmd)
	{
		case 0://ֹͣ
			UART1_SendString("000xxxx");
			MT_Stop();
			break;
		case 1://ǰ��
			MT_Forward();
			break;
		case 2://����
			MT_Backward();
			break;
		case 3://��ת
			MT_TurnLeft();
			break;
		case 4://��ת
			MT_TurnRight();
			break;
		case 5://����
			MT_ChangeSpeed();
			break;
		default:
			break;
	}
}

//����1�жϣ��жϺ�4
void UART1_ISR(void) interrupt 4
{
	//���ڽ��յ�������
	u8 uart_rec_data = 0;
	/*���ڽ���*/
	if(RI)
	{
		RI = 0;//����жϱ�־
		uart_rec_data = SBUF;//������������
		Handle_UART_CMD(uart_rec_data);
    }
	if(TI)
	{
		TI = 0;
    }
}

