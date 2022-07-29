#ifndef _INFRARED_H
#define _INFRARED_H
#include "Delay.h"
#include "stc15w4k58s4.h"

sbit IR_D0 = P4^1;	//P4.1  29½Å
sbit IR_A0 = P4^2;	//P4.2  30½Å

//u16 SR_GetDis(void);
//void SR_SendTrig(void);
void IR_Init(void);
u8 Get_Trace_State(void);

#endif