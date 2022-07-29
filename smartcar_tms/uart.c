#include"uart.h"
#include "LCD12864.h"
#include "motor.h"

//串口初始化，9600bps@12MHz
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

//串口发送一个char
void UART1_SendData(unsigned char dat)
{
	SBUF = dat;
	TI = 0;
	while(!TI);
}

//串口发送字符串
void UART1_SendString(char *str)
{
	unsigned char idx = 0;
	while(*(str+idx)!='\0')
	{
		UART1_SendData(*(str+idx));
		idx++;
  	}

}

//处理串口命令
void Handle_UART_CMD(u8 cmd)
{
	switch(cmd)
	{
		case 0://停止
			UART1_SendString("000xxxx");
			MT_Stop();
			break;
		case 1://前进
			MT_Forward();
			break;
		case 2://后退
			MT_Backward();
			break;
		case 3://左转
			MT_TurnLeft();
			break;
		case 4://右转
			MT_TurnRight();
			break;
		case 5://调速
			MT_ChangeSpeed();
			break;
		default:
			break;
	}
}

//串口1中断，中断号4
void UART1_ISR(void) interrupt 4
{
	//串口接收到的数据
	u8 uart_rec_data = 0;
	/*串口接收*/
	if(RI)
	{
		RI = 0;//清除中断标志
		uart_rec_data = SBUF;//读出串口数据
		Handle_UART_CMD(uart_rec_data);
    }
	if(TI)
	{
		TI = 0;
    }
}

