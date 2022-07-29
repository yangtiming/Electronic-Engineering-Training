#ifndef _SONIC_H
#define _SONIC_H
#include "Delay.h"
#include "stc15w4k58s4.h"

sbit SR_Trig = P3^5;	//P3.5
sbit SR_Echo = P3^4;	//P3.4

u16 SR_GetDis(void);
void SR_SendTrig(void);
void SR_Init(void);

#endif