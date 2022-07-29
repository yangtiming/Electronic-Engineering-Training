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
// ����: void   CheckBusy(void)
// ����: ���æ����
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
//========================================================================
void    CheckBusy(void)
{
    long int i;
    for(i=0; i<5000; i++)   {if(!LCD_B7)    break;}     //check the LCD busy or not. With time out
//  while(LCD_B7);          //check the LCD busy or not. Without time out
}


//========================================================================
// ����: void CMD_Send_Init(unsigned char cmd)
// ����: ��ʼ��д����(�����æ)
// ����: cmd: Ҫд������.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
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
// ����: void Write_CMD(unsigned char  cmd)
// ����: д����(���æ)
// ����: cmd: Ҫд������.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
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
// ����: void Write_DIS_Data(unsigned char  dat)
// ����: д��ʾ����(���æ)
// ����: dat: Ҫд������.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
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
// ����: void LCD_Init(void)
// ����: ��ʼ������
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
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
// ����: void Clear_Line(unsigned char row)
// ����: ���1��
// ����: row: ��(0��1)
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
//========================================================================
void Clear_Line(unsigned char row)
{
    unsigned char i;
    Write_CMD(((row & 1) << 6) | 0x80);
    for(i=0; i<LineLength; i++) Write_DIS_Data(' ');
}

//========================================================================
// ����: void   WriteChar(u8 row, u8 column, u8 dat)
// ����: ָ���С��к��ַ�, дһ���ַ�
// ����: row: ��(0��1),  column: �ڼ����ַ�(0~15),  dat: Ҫд���ַ�.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
//========================================================================
void  Write_Char(unsigned char row,unsigned char column,unsigned char dat)
{
    Write_CMD((((row & 1) << 6) + column) | 0x80);
    Write_DIS_Data(dat);
}

//========================================================================
// ����: void PutString(unsigned char row,unsigned char column,unsigned char *puts)
// ����: дһ���ַ�����ָ���С��к��ַ����׵�ַ
// ����: row: ��(0��1),  column: �ڼ����ַ�(0~15),  puts: Ҫд���ַ���ָ��.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
//========================================================================
void PutString(unsigned char row, unsigned char column,unsigned char *puts)
{
    Write_CMD((((row & 1) << 6) + column) | 0x80);
    for ( ;  *puts != 0;  puts++)       //����ֹͣ��0����
    {
        Write_DIS_Data(*puts);
        if(++column >= LineLength)  break;
    }
}

//========================================================================
// ����: void Write_Num(unsigned char row, unsigned char column, unsigned char *puts)
// ����: д����
// ����: row: ��(0��1),  column: �ڼ����ַ�(0~15),  dat Ҫд������
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
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