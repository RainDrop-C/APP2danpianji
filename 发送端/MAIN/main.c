#include <reg52.h>
#include "AD.H"
#include "Delay.h" 
#include "nrf2401.h"
#include "Usart.h"

unsigned char TXD_Date[4]; //NRF24L01发送的数据

void main(void)
{
	Init_Usart();
	NRF24L01Int();//2401初始化
	P0=0x00;
	while(1)	             
	{	
		Test();
	  	TXD_Date[0]=Send_Advalue();	
		TXD_Date[1]=21;
		TXD_Date[2]=22;
		TXD_Date[3]=23;
		SendByte(TXD_Date[0]);
		CheckACK();
		NRFSetTxMode(TXD_Date);//发送数据		 
	}
}