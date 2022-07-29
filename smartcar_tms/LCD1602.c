#include"LCD1602.h"


//========================================================================
void LCD_BusData(dat)
{
	 LCD_B7  = (dat&(0x01<<7))>>7;    //D7 -- Pin 8    
	 LCD_B6  = (dat&(0x01<<6))>>6;    //D6 -- Pin 7     
	 LCD_B5  = (dat&(0x01<<5))>>5;    //D5 -- Pin 6    
	 LCD_B4  = (dat&(0x01<<4))>>4;    //D4 -- Pin 5      
	 LCD_B3  = (dat&(0x01<<3))>>3;    //D3 -- Pin 4      
	 LCD_B2  = (dat&(0x01<<2))>>2;    //D2 -- Pin 3 
	 LCD_B1  = (dat&(0x01<<1))>>1;    //D1 -- Pin 2
	 LCD_B0  = (dat&(0x01<<0))>>0;    //D0 -- Pin 1
}


//========================================================================
// 函数: void   CheckBusy(void)
// 描述: 检测忙函数
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void    CheckBusy(void)
{
    long int i;
    for(i=0; i<5000; i++)   {if(!LCD_B7)    break;}     //check the LCD busy or not. With time out
//  while(LCD_B7);          //check the LCD busy or not. Without time out
}


//========================================================================
// 函数: void CMD_Send_Init(unsigned char cmd)
// 描述: 初始化写命令(不检测忙)
// 参数: cmd: 要写的命令.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void CMD_Send_Init(unsigned char cmd)
{
    LCD_RW = 0;
    LCD_BusData(cmd);
    LCD_DelayNop();
    LCD_ENA = 1;
    LCD_DelayNop();
    LCD_ENA = 0;
    LCD_BusData(0xff);
}

//========================================================================
// 函数: void Write_CMD(unsigned char  cmd)
// 描述: 写命令(检测忙)
// 参数: cmd: 要写的命令.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void Write_CMD(unsigned char  cmd)
{
    LCD_RS  = 0;
    LCD_RW = 1;
    LCD_BusData(0xff);
    LCD_DelayNop();
    LCD_ENA = 1;
    CheckBusy();            //check the LCD busy or not.
    LCD_ENA = 0;
    LCD_RW = 0;
    
    LCD_BusData(cmd);
    LCD_DelayNop();
    LCD_ENA = 1;
    LCD_DelayNop();
    LCD_ENA = 0;
    LCD_BusData(0xff);
}

//========================================================================
// 函数: void Write_DIS_Data(unsigned char  dat)
// 描述: 写显示数据(检测忙)
// 参数: dat: 要写的数据.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void Write_DIS_Data(unsigned char dat)
{
    LCD_RS = 0;
    LCD_RW = 1;

    LCD_BusData(0xff);
    LCD_DelayNop();
    LCD_ENA = 1;
    CheckBusy();            //check the LCD busy or not.
    LCD_ENA = 0;
    LCD_RW = 0;
    LCD_RS  = 1;

    LCD_BusData(dat);
    LCD_DelayNop();
    LCD_ENA = 1;
    LCD_DelayNop();
    LCD_ENA = 0;
    LCD_BusData(0xff);
}


//========================================================================
// 函数: void LCD_Init(void)
// 描述: 初始化函数
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
 void LCD_Init(void)
{
    LCD_ENA = 0;
    LCD_RS  = 0;
    LCD_RW = 0;

    Delay_Nms(100);
    CMD_Send_Init(C_BIT8);     //set the data is 8 bits

    Delay_Nms(10);
    Write_CMD(C_L2DOT7);        //tow lines 5*7 dots

    Delay_Nms(6);
    Write_CMD(C_CLEAR);     //clear LCD RAM
    Write_CMD(C_CUR_R);     //Curror Shift Right
    Write_CMD(C_ON);        //turn on  LCD
	Clear_Line(0);
	Clear_Line(1);
}



//========================================================================
// 函数: void Clear_Line(unsigned char row)
// 描述: 清除1行
// 参数: row: 行(0或1)
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void Clear_Line(unsigned char row)
{
    unsigned char i;
    Write_CMD(((row & 1) << 6) | 0x80);
    for(i=0; i<LineLength; i++) Write_DIS_Data(' ');
}

//========================================================================
// 函数: void   WriteChar(u8 row, u8 column, u8 dat)
// 描述: 指定行、列和字符, 写一个字符
// 参数: row: 行(0或1),  column: 第几个字符(0~15),  dat: 要写的字符.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void  Write_Char(unsigned char row,unsigned char column,unsigned char dat)
{
    Write_CMD((((row & 1) << 6) + column) | 0x80);
    Write_DIS_Data(dat);
}

//========================================================================
// 函数: void PutString(unsigned char row,unsigned char column,unsigned char *puts)
// 描述: 写一个字符串，指定行、列和字符串首地址
// 参数: row: 行(0或1),  column: 第几个字符(0~15),  puts: 要写的字符串指针.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void PutString(unsigned char row, unsigned char column,unsigned char *puts)
{
    Write_CMD((((row & 1) << 6) + column) | 0x80);
    for ( ;  *puts != 0;  puts++)       //遇到停止符0结束
    {
        Write_DIS_Data(*puts);
        if(++column >= LineLength)  break;
    }
}

//========================================================================
// 函数: void Write_Num(unsigned char row, unsigned char column, unsigned char *puts)
// 描述: 写数字
// 参数: row: 行(0或1),  column: 第几个字符(0~15),  dat 要写的数字
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void Write_Num(unsigned char row,unsigned char column,long int dat)
{
	
	unsigned char num[8];
	unsigned char  i=0;
	unsigned char j;
	while(dat){
	num[i]=dat%10+'0';
	dat=dat/10;
	i++;
	}
	j=0;
	if(i==0){
	Write_Char(row,column+i-j,' ');
	Write_Char(row,column,'0');
	}
	i--;
	while(j<=i){
	Write_Char(row,column+i-j,' ');
	Write_Char(row,column+i-j,num[j]);
	j++;
	}
	
}