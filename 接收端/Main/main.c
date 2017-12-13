#include <reg52.h>
#include "delay.h"
#include "Usart.h"
#include "12864.h"
#include "NRF2401.h"
#include "oled.h"



void Deal_CarData(unsigned char i,unsigned char t)
{
 switch(i)
 {
 case 0:OLED_ShowNum(t,6,0,4,16);  break;
 case 1:OLED_ShowNum(t,6,1,4,16);  break;
 case 2:OLED_ShowNum(t,6,10,4,16);  break;
 case 3:OLED_ShowNum(t,6,11,4,16);  break;
 case 4:OLED_ShowNum(t,6,100,4,16);  break;
 case 5:OLED_ShowNum(t,6,101,4,16);  break;
 case 6:OLED_ShowNum(t,6,110,4,16);  break;
 case 7:OLED_ShowNum(t,6,111,4,16);  break;
 case 8:OLED_ShowNum(t,6,1000,4,16);  break;
 case 9:OLED_ShowNum(t,6,1001,4,16);  break;
 case 10:OLED_ShowNum(t,6,1010,4,16); break;
 case 11:OLED_ShowNum(t,6,1011,4,16); break;
 case 12:OLED_ShowNum(t,6,1100,4,16); break;
 case 13:OLED_ShowNum(t,6,1101,4,16); break;
 case 14:OLED_ShowNum(t,6,1110,4,16); break;
 case 15:OLED_ShowNum(t,6,1111,4,16); break;
 default:break;
 }
}


void main(void) 
{
	unsigned char x=0;
//	Init_Usart();
//	NRF24L01Int(); 	   // NRF24L01初始化
//	init_12864();
	OLED_Init();
	while(1)
	{
		Menu_Display(x);
		x++;
		delay_ms(500);
	/*NRFSetRXMode();//设置为接收模式
	GetDate();//开始接受数
	display_distance2(2,3,RevTempDate[0]);
	display_distance2(1,4,RevTempDate[1]);
	display_distance2(3,4,RevTempDate[2]);
	display_distance2(5,4,RevTempDate[3]);
	Send_Data(RevTempDate[0]); 	
	OLED_ShowNum(41,4,RevTempDate[0]/100,1,16);
	OLED_ShowNum(49,4,RevTempDate[0]/10%10,1,16);
	OLED_ShowNum(57,4,RevTempDate[0]%10,1,16);
	Deal_CarData(RevTempDate[0]&0x0f,50);
    Deal_CarData(RevTempDate[0]>>4,10);*/
	}
}

