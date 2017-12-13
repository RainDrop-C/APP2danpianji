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
*   �������ܣ�����д������			 *
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

/*******��ʼ������********/
void init_12864(void)  //�˾�д�������������ڳ�ʼ��12864
{    
	 
 	 write_com(0x30);  //����ָ�����
	 delay_ms(10);
	 write_com(0x0c);  //����ʾ���ع��
	 delay_ms(10);
	 write_com(0x01);   //���LCD����ʾ����
	 delay_ms(10);	
	// display_string(0,1,"���ҵ���");
	 display_string(0,2,"��λռ�����");

}

/***************������ʾλ�ú���********************/
void display_string(unsigned char x,unsigned char y,unsigned char *s)
{ 
     switch(y)
     {
	  	 case 1: write_com(0x80+x);break;  //12864��һ��
	     case 2: write_com(0x90+x);break;   //12864�ڶ���
	     case 3: write_com(0x88+x);break;    //12864������
	     case 4: write_com(0x98+x);break;   //12864������
         default:break;		  
	 }
     while(*s)
     { 
        write_date(*s);    //��ʾ�ַ���
		delay_ms(10);
        s++;
     }
}

//void display_distance1(uchar x,uchar y,uint num2) //��ʾ����
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
//	 a=num2/100;//shiλ
//     b=num2/10%10;//geλ
//	 c=num2%10;//-temp2*(temp<=28 ? -1:1);//xiaoshuλ
//     
//	 write_date(a+0x30);	 //ascii��ת��Ϊ����������
//	 write_date(b+0x30);
//     write_date('.');	 
//	 write_date(c+0x30);
//}

void display_distance2(uchar x,uchar y,uint num1) //��ʾ����
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

	 a=num1/100;//��λ
     b=num1/10%10;//ʮλ
	 c=num1%10;//��λ
     
	 write_date(a+0x30);	 //ascii��ת��Ϊ����������
	 write_date(b+0x30);	 
	 write_date(c+0x30);
}