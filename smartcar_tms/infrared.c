#include "infrared.h"

u8 trace_state = 0;

void IR_Init(void)	//��ʼ������ѭ��ģ��
{
	P4M0 = 0;
	P4M1 = 0;
	EA = 1;
}

u8 Get_Trace_State(void)  //D0Ϊ�߱�ʾ����Ϊ�ͱ�ʾ��
{
	trace_state = P41;
	return trace_state;
}
