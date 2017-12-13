#include <reg52.h>
#include "intrins.h"
#include "delay.h" 

/*************************************************** 
*�������ƣ�void delay(unsigned int time)
*���������time����ʱʱ��
*����ֵ����
*���ܣ�ģ����ʱ
*ʱ�䣺2016-4-15
*ʹ�ã�delay(5000);
****************************************************/
void delay(unsigned int time) //int������Ϊ16λ,�������ֵΪ65535            
{
	unsigned int i,j;            
	for(i=0;i<time;i++)          
		for(j=0;j<50;j++);      
} 

/***************************************************
*�������ƣ�void delay_ms(void)
*�����������
*����ֵ����
*���ܣ�1ms��ʱ
*ʱ�䣺2016-4-15
*ʹ�ã�delay_ms();
***************************************************/
void delayms(void)		//@11.0592MHz
{
	unsigned char i,j;
	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} 
	while (--i);
}

void delay_ms(unsigned int time)
{
	unsigned int i;
	for(i=0;i<time;i++)
		delayms();
}
/**************************************************
*�������ƣ�void delay_us(void)
*�����������
*����ֵ����
*���ܣ�1us��ʱ
*ʱ�䣺2016-4-15
*ʹ�ã�delay_us();
**************************************************/
void delayus(void)		//@11.0592MHz
{
	_nop_();
	_nop_();
	_nop_();
}

void delay_us(unsigned int time)
{
	unsigned int i;
	for(i=0;i<time;i++)
		delayus();
}
/****************************************************** 
*�������ƣ�void delay_s(void)
*����μӣ���
*����ֵ����
*���ܣ�1us��ʱ
*ʱ�䣺2016-4-15
*ʹ�ã�delay_us();
******************************************************/
void delay_s(void)		//@11.0592MHz
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} 	while (--j);
	} 
	while (--i);
}


void delay_n_s(unsigned int i)
{
	unsigned int j; 
	for(j=0;j<i;j++)
	delay_s();
}












