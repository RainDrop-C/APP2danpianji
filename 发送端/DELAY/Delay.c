#include <reg52.h>
#include "intrins.h"
#include "delay.h" 

/*************************************************** 
*函数名称：void delay(unsigned int time)
*输入参数：time，延时时间
*返回值：无
*功能：模糊延时
*时间：2016-4-15
*使用：delay(5000);
****************************************************/
void delay(unsigned int time) //int型数据为16位,所以最大值为65535            
{
	unsigned int i,j;            
	for(i=0;i<time;i++)          
		for(j=0;j<50;j++);      
} 

/***************************************************
*函数名称：void delay_ms(void)
*输入参数：无
*返回值：无
*功能：1ms延时
*时间：2016-4-15
*使用：delay_ms();
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
*函数名称：void delay_us(void)
*输入参数：无
*返回值：无
*功能：1us延时
*时间：2016-4-15
*使用：delay_us();
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
*函数名称：void delay_s(void)
*输入参加：无
*返回值：无
*功能：1us延时
*时间：2016-4-15
*使用：delay_us();
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












