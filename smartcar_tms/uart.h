#include<STC15W4K58S4.H>
#include "intrins.h"

void UART_Init(void);
void UART1_SendData(unsigned char dat);
void UART1_SendString(char *str);
void Handle_UART_CMD(u8 cmd);