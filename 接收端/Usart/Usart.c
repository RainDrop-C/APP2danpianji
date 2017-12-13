#include<reg52.h>
#include "delay.h"

void Init_Usart(void)
{
    SCON  = 0x50;		        // SCON: 模式 1, 8-bit UART, 使能接收  
    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit 重装
    TH1   = 0xFD;               // TH1:  重装值 9600 波特率 晶振 11.0592MHz  
    TR1   = 1;                  // TR1:  timer 1 打开                         
    EA    = 1;                  //打开总中断
    //ES    = 1;                  //打开串口中断
}    

void SendByte(unsigned char dat)
{
 SBUF = dat;
 while(!TI);
 TI = 0;
}


void Send_Data(unsigned char i)
{
 SendByte(i);
 delay_s();
}	 
