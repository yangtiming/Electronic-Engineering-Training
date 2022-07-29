#include "sonic.h"

//当前距离，单位 cm
u16 cur_dis = 0xffff;

//超声波模块初始化
void SR_Init(void)
{
	//P3端口模式，P3.0和P3.1连接echo和trig
	P3M0 = 0;
	P3M1 = 0;
    EA = 1;
}

//发送触发信号
void SR_SendTrig(void)
{
	u16 len = 0;
	TMOD = 0x01;				//设置计时器
	TH0 = 0;
	TL0 = 0;
	ET0 = 0;
	SR_Trig = 1;
	Delay10us();
	SR_Trig = 0;
	while(!SR_Echo);			//开始计时
	TR0 = 1;
	while(SR_Echo);				//结束计时
	TR0 = 0;
	len = (TH0 << 8) + TL0;	//计算距离
	cur_dis = (u16)(len * 1.7 / 100);
	TH0 = 0;
	TL0 = 0;
}

//返回当前距离
u16 SR_GetDis(void)
{
    return cur_dis;
}