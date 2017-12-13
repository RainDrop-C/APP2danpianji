#include <reg52.h>
#include "AD.H"
#include "Delay.h"
#include "Usart.h"

sbit  Car1 = P1^0;	   //一号车位对应的单片机P1^0检测口
sbit  Car2 = P1^1;	   //二号车位对应的单片机P1^1检测口
sbit  Car3 = P1^2;	   //三号车位对应的单片机P1^2检测口
sbit  Car4 = P1^3;	   //四号车位对应的单片机P1^3检测口
sbit  Car5 = P1^4;	   //五号车位对应的单片机P1^4检测口
sbit  Car6 = P1^5;	   //六号车位对应的单片机P1^5检测口
sbit  Car7 = P1^6;	   //七号车位对应的单片机P1^6检测口
sbit  Car8 = P1^7;	   //八号车位对应的单片机P1^7检测口

unsigned char temp[8];

unsigned char  Send_Advalue(void)
{
   unsigned char Num_1=0;
   Num_1=((temp[7]<<7)|(temp[6]<<6)|(temp[5]<<5)|(temp[4]<<4)|(temp[3]<<3)|(temp[2]<<2)|(temp[1]<<1)|(temp[0])); 
   delay_n_s(1); 
   return  Num_1;
}


void Test(void)
{
	if(Car1==1){   delay_ms(10); if(Car1==1){ temp[0]=0;}   }
	if(Car2==1){   delay_ms(10); if(Car2==1){ temp[1]=0;}   }
	if(Car3==1){   delay_ms(10); if(Car3==1){ temp[2]=0;}   }
	if(Car4==1){   delay_ms(10); if(Car4==1){ temp[3]=0;}   }
	if(Car5==1){   delay_ms(10); if(Car5==1){ temp[4]=0;}   }
	if(Car6==1){   delay_ms(10); if(Car6==1){ temp[5]=0;}   }
	if(Car7==1){   delay_ms(10); if(Car7==1){ temp[6]=0;}   }
	if(Car8==1){   delay_ms(10); if(Car8==1){ temp[7]=0;}   }

	if(Car1==0){   delay_ms(10); if(Car1==0){ temp[0]=1;}   }
	if(Car2==0){   delay_ms(10); if(Car2==0){ temp[1]=1;}   }
	if(Car3==0){   delay_ms(10); if(Car3==0){ temp[2]=1;}   }
	if(Car4==0){   delay_ms(10); if(Car4==0){ temp[3]=1;}   }
	if(Car5==0){   delay_ms(10); if(Car5==0){ temp[4]=1;}   }
	if(Car6==0){   delay_ms(10); if(Car6==0){ temp[5]=1;}   }
	if(Car7==0){   delay_ms(10); if(Car7==0){ temp[6]=1;}   }
	if(Car8==0){   delay_ms(10); if(Car8==0){ temp[7]=1;}   }
}













