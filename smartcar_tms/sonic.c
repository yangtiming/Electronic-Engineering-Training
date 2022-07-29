#include "sonic.h"

//��ǰ���룬��λ cm
u16 cur_dis = 0xffff;

//������ģ���ʼ��
void SR_Init(void)
{
	//P3�˿�ģʽ��P3.0��P3.1����echo��trig
	P3M0 = 0;
	P3M1 = 0;
    EA = 1;
}

//���ʹ����ź�
void SR_SendTrig(void)
{
	u16 len = 0;
	TMOD = 0x01;				//���ü�ʱ��
	TH0 = 0;
	TL0 = 0;
	ET0 = 0;
	SR_Trig = 1;
	Delay10us();
	SR_Trig = 0;
	while(!SR_Echo);			//��ʼ��ʱ
	TR0 = 1;
	while(SR_Echo);				//������ʱ
	TR0 = 0;
	len = (TH0 << 8) + TL0;	//�������
	cur_dis = (u16)(len * 1.7 / 100);
	TH0 = 0;
	TL0 = 0;
}

//���ص�ǰ����
u16 SR_GetDis(void)
{
    return cur_dis;
}