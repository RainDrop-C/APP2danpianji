#include<reg52.h>
#include "nrf2401.h"
#include "delay.h"

sbit CE   = P2^5;     //RX/TXģʽѡ���
sbit CSN  = P2^0;    //SPIƬѡ��//����SS
sbit SCLK = P2^4;	 //SPIʱ�Ӷ�
sbit MOSI = P2^1;	 //SPI��������ӻ������
sbit MISO = P2^3;	 //SPI��������ӻ������
sbit IRQ  = P2^2;   //�������ж϶�	
/*����������趨���ݵõ���ͣ��λ���Ӻõĵ�·*/	

uchar code TxAddr[]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ

/*****************״̬��־*****************************************/
uchar  bdata sta;   //״̬��־
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;
sbit MAX_RT=sta^4;

/*****************SPIʱ����******************************************/
uchar NRFSPI(uchar date)
{
    uchar i;
   	for(i=0;i<8;i++)          // ѭ��8��
   	{
	  if(date&0x80)
	    MOSI=1;
	  else
	    MOSI=0;   // byte���λ�����MOSI
   	  date<<=1;             // ��һλ��λ�����λ
   	  SCLK=1; 
	  if(MISO)               // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
   	    date|=0x01;       	// ��MISO��byte���λ
   	  SCLK=0;            	// SCK�õ�
   	}
    return(date);           	// ���ض�����һ�ֽ�
}
/**********************NRF24L01��ʼ������*******************************/
void NRF24L01Int()
{
	delay_ms(2);//��ϵͳʲô������
	CE=0;
	CSN=1;  
	SCLK=0;
	IRQ=1; 
}
/*****************SPI���Ĵ���һ�ֽں���*********************************/
uchar NRFReadReg(uchar RegAddr)
{
   uchar BackDate;
   CSN=0;//����ʱ��
   NRFSPI(RegAddr);//д�Ĵ�����ַ
   BackDate=NRFSPI(0x00);//д����Ĵ���ָ��  
   CSN=1;
   return(BackDate); //����״̬
}
/*****************SPIд�Ĵ���һ�ֽں���*********************************/
uchar NRFWriteReg(uchar RegAddr,uchar date)
{
   uchar BackDate;
   CSN=0;//����ʱ��
   BackDate=NRFSPI(RegAddr);//д���ַ
   NRFSPI(date);//д��ֵ
   CSN=1;  
   return(BackDate);
}


/*****************SPIд��TXFIFO�Ĵ�����ֵ**********************************/
uchar NRFWriteTxDate(uchar RegAddr,uchar *TxDate,uchar DateLen)
{ //�Ĵ�����ַ//д�����ݴ�ű���//��ȡ���ݳ���//���ڷ���
   uchar BackDate,i;
   CSN=0;
   BackDate=NRFSPI(RegAddr);//д��Ҫд��Ĵ����ĵ�ַ
   for(i=0;i<DateLen;i++)//д������
     {
	    NRFSPI(*TxDate++);
	 }   
   CSN=1;
   return(BackDate);
}
/*****************NRF����Ϊ����ģʽ����������******************************/
void NRFSetTxMode(uchar *TxDate)
{  //����ģʽ 
    CE=0;   
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//д�Ĵ���ָ��+P0��ַʹ��ָ��+���͵�ַ+��ַ���
	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//д������ 
	/******�����йؼĴ�������**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);         // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	NRFWriteReg(W_REGISTER+CONFIG,0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�	
	CE=1;	
	delay_ms(5);//����10us������
} 

/****************************����Ƿ��н��յ�����******************************/
uchar  CheckACK()
{  																								 //���ڷ���
sta=NRFReadReg(R_REGISTER+STATUS);                    // ����״̬�Ĵ���
	if(TX_DS||MAX_RT) //��������ж�
	{
	   NRFWriteReg(W_REGISTER+STATUS,0xff);  // ���TX_DS��MAX_RT�жϱ�־
	   CSN=0;
	   NRFSPI(FLUSH_TX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס����  
       CSN=1; 
	   return(0);
	}
	else
	   return(1);
}
