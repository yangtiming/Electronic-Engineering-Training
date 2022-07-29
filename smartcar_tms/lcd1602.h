
/************* LCD1602相关程序  *****************************************************/
//8位数据访问方式   LCD1602     标准程序    梁工编写    2014-2-21
#ifndef __LCD1602_H_
#define __LCD1602_H_
#include<STC15W4K58S4.H>
#include "delay.h"
#include "intrins.h"
#define LineLength  16      //16x2

/*************  Pin define  *****************************************************/

sbit    LCD_B7  = P2^0;    //D7 -- Pin 8       
sbit    LCD_B6  = P2^1;    //D6 -- Pin 7    
sbit    LCD_B5  = P2^2;    //D5 -- Pin 6      
sbit    LCD_B4  = P2^3;    //D4 -- Pin 5    
sbit    LCD_B3  = P2^4;    //D3 -- Pin 4      
sbit    LCD_B2  = P2^5;    //D2 -- Pin 3
sbit    LCD_B1  = P2^6;    //D1 -- Pin 2
sbit    LCD_B0  = P2^7;    //D0 -- Pin 1

sbit    LCD_ENA = P0^5; //Pin 14
sbit    LCD_RW  = P0^6; //Pin 13 //LCD_RS   R/W   DB7--DB0        FOUNCTION
sbit    LCD_RS  = P0^7; //Pin 12 //  0       0     INPUT      write the command to LCD model
                                //  0       1     OUTPUT     read BF and AC pointer from LCD model
                                //  1       0     INPUT      write the data to LCD  model
                                //  1       1     OUTPUT     read the data from LCD model
/*
total 2 lines, 16x2= 32
first line address:  0~15
second line address: 64~79

*/

#define C_CLEAR         0x01        //clear LCD
#define C_HOME          0x02        //cursor go home
#define C_CUR_L         0x04        //cursor shift left after input
#define C_RIGHT         0x05        //picture shift right after input
#define C_CUR_R         0x06        //cursor shift right after input
#define C_LEFT          0x07        //picture shift left after input
#define C_OFF           0x08        //turn off LCD
#define C_ON            0x0C        //turn on  LCD
#define C_FLASH         0x0D        //turn on  LCD, flash 
#define C_CURSOR        0x0E        //turn on  LCD and cursor
#define C_FLASH_ALL     0x0F        //turn on  LCD and cursor, flash
#define C_CURSOR_LEFT   0x10        //single cursor shift left
#define C_CURSOR_RIGHT  0x10        //single cursor shift right
#define C_PICTURE_LEFT  0x10        //single picture shift left
#define C_PICTURE_RIGHT 0x10        //single picture shift right
#define C_BIT8          0x30        //set the data is 8 bits
#define C_BIT4          0x20        //set the data is 4 bits
#define C_L1DOT7        0x30        //8 bits,one line 5*7  dots
#define C_L1DOT10       0x34        //8 bits,one line 5*10 dots
#define C_L2DOT7        0x38        //8 bits,tow lines 5*7 dots
#define C_4bitL2DOT7    0x28        //4 bits,tow lines 5*7 dots
#define C_CGADDRESS0    0x40        //CGRAM address0 (addr=40H+x)
#define C_DDADDRESS0    0x80        //DDRAM address0 (addr=80H+x)

#define LCD_DelayNop()  _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();\
                        _nop_();


void LCD_Bus_Data(dat);
void CheckBusy(void);
void CMD_Send_Init(unsigned char cmd);
void Write_CMD(unsigned char  cmd);
void Write_DIS_Data(unsigned char dat);
void LCD_Init(void);
void Clear_Line(unsigned char row);
void Write_Char(unsigned char row, unsigned char column,unsigned char dat);
void PutString(unsigned char row, unsigned char column, unsigned char *puts);
void Write_Num(unsigned char row, unsigned char column, long int dat);
void Delay1ms(void);
void Delay_Nms(unsigned int n_ms);
#endif