#include<reg52.h>
#include "delay.h"

void Init_Usart(void)
{
    SCON  = 0x50;		        // SCON: ģʽ 1, 8-bit UART, ʹ�ܽ���  
    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit ��װ
    TH1   = 0xFD;               // TH1:  ��װֵ 9600 ������ ���� 11.0592MHz  
    TR1   = 1;                  // TR1:  timer 1 ��                         
    EA    = 1;                  //�����ж�
    //ES    = 1;                  //�򿪴����ж�
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
