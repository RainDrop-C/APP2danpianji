#include<reg52.h>
#include <intrins.h>
#include"12864.h"
#include "delay.h"
sbit RW=P0^1; 
sbit EN=P0^0;

void write_com(uchar  com)
{
	uchar i;
	EN=0;
	RW=1;
	for(i=0;i<5;i++)
	{
	 	EN=1;
		EN=0;			
	}
	RW=0;EN=1;EN=0;
	RW=0;EN=1;EN=0;
	RW=0;EN=1;EN=0;
	for(i=0;i<4;i++)
	{
		RW=(bit)(com & (0x80) );
		EN=1;
		EN=0;
		com=com<<1; 	
	}
	RW=0;
	for(i=0;i<4;i++)
	{
	 	EN=1;
		EN=0;
	}
	delay_ms(10);
	for(i=0;i<4;i++)
	{
	 	RW=(bit)(com & (0x80));
		EN=1;
		EN=0;
		com=com <<1;
	}
	RW=0;
	for(i=0;i<4;i++)
	{
	 	EN=1;
		EN=0;
	}		
}

/*************************************
*   函数功能：串口写入数据			 *
**************************************/
void write_date(uchar date)
{
	uchar i;
	EN=0;
	RW=1;
	for(i=0;i<5;i++)
	{
	 	EN=1;
		EN=0;			
	}
	RW=0;EN=1;EN=0;
	RW=1;EN=1;EN=0;
	RW=0;EN=1;EN=0;
	for(i=0;i<4;i++)
	{
		RW=(bit)(date & (0x80) );
		EN=1;
		EN=0;
		date=date<<1; 	
	}
	RW=0;
	for(i=0;i<4;i++)
	{
	 	EN=1;
		EN=0;
	}
	delay_ms(10);
	for(i=0;i<4;i++)
	{
	 	RW=(bit)(date & (0x80));
		EN=1;
		EN=0;
		date=date<<1;
	}
	RW=0;
	for(i=0;i<4;i++)
	{
	 	EN=1;
		EN=0;
	}					
}

/*******初始化函数********/
void init_12864(void)  //此句写在主函数中用于初始化12864
{    
	 
 	 write_com(0x30);  //基本指令操作
	 delay_ms(10);
	 write_com(0x0c);  //开显示，关光标
	 delay_ms(10);
	 write_com(0x01);   //清除LCD的显示内容
	 delay_ms(10);	
	// display_string(0,1,"李敬毕业设计");
	 display_string(0,2,"车位占空情况");

}

/***************设置显示位置函数********************/
void display_string(unsigned char x,unsigned char y,unsigned char *s)
{ 
     switch(y)
     {
	  	 case 1: write_com(0x80+x);break;  //12864第一行
	     case 2: write_com(0x90+x);break;   //12864第二行
	     case 3: write_com(0x88+x);break;    //12864第三行
	     case 4: write_com(0x98+x);break;   //12864第四行
         default:break;		  
	 }
     while(*s)
     { 
        write_date(*s);    //显示字符串
		delay_ms(10);
        s++;
     }
}

//void display_distance1(uchar x,uchar y,uint num2) //显示距离
//{ 
//   uchar a,b,c;
//   switch(y)
//     {
//	  case 1: write_com(0x80+x);break;
//	  case 2: write_com(0x90+x);break;
//	  case 3: write_com(0x88+x);break;
//	  case 4: write_com(0x98+x);break;
//			default:break;
//	}
//
//	 a=num2/100;//shi位
//     b=num2/10%10;//ge位
//	 c=num2%10;//-temp2*(temp<=28 ? -1:1);//xiaoshu位
//     
//	 write_date(a+0x30);	 //ascii码转化为阿拉伯数字
//	 write_date(b+0x30);
//     write_date('.');	 
//	 write_date(c+0x30);
//}

void display_distance2(uchar x,uchar y,uint num1) //显示距离
{ 
   uchar a,b,c;
   switch(y)
     {
	  case 1: write_com(0x80+x);break;
	  case 2: write_com(0x90+x);break;
	  case 3: write_com(0x88+x);break;
	  case 4: write_com(0x98+x);break;
			default:break;
	}

	 a=num1/100;//百位
     b=num1/10%10;//十位
	 c=num1%10;//个位
     
	 write_date(a+0x30);	 //ascii码转化为阿拉伯数字
	 write_date(b+0x30);	 
	 write_date(c+0x30);
}