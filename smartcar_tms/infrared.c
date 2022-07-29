#include "infrared.h"

u8 trace_state = 0;

void IR_Init(void)	//初始化红外循迹模块
{
	P4M0 = 0;
	P4M1 = 0;
	EA = 1;
}

u8 Get_Trace_State(void)  //D0为高表示亮，为低表示暗
{
	trace_state = P41;
	return trace_state;
}
