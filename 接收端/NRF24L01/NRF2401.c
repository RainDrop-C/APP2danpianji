#include<reg52.h>
#include"NRF2401.h"
#include"delay.h"

sbit CE   = P2^3;     //RX/TXģʽѡ���
sbit CSN  = P2^0;    //SPIƬѡ��//����SS
sbit SCLK = P2^4;	 //SPIʱ�Ӷ�
sbit MOSI = P2^1;	 //SPI��������ӻ������
sbit MISO = P2^5;	 //SPI��������ӻ������
sbit IRQ  = P2^2;   //�������ж϶�		
/*
sbit CE   = P2^5;     //RX/TXģʽѡ���
sbit CSN  = P2^0;    //SPIƬѡ��//����SS
sbit SCLK = P2^4;	 //SPIʱ�Ӷ�
sbit MOSI = P2^1;	 //SPI��������ӻ������
sbit MISO = P2^3;	 //SPI��������ӻ������
sbit IRQ  = P2^2;   //�������ж϶�
*/	
uchar RevTempDate[4]={0};//���һλ������Ž�����־
uchar code TxAddr[]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ

/*****************״̬��־*****************************************/
uchar  bdata sta;   //״̬��־
sbit RX_DR  = sta^6;
sbit TX_DS  = sta^5;
sbit MAX_RT = sta^4;

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

/*****************SPI��ȡRXFIFO�Ĵ�����ֵ********************************/
uchar NRFReadRxDate(uchar RegAddr,uchar *RxDate,uchar DateLen)
{  //�Ĵ�����ַ//��ȡ���ݴ�ű���//��ȡ���ݳ���//���ڽ���
    uchar BackDate,i;
	CSN=0;//����ʱ��
	BackDate=NRFSPI(RegAddr);//д��Ҫ��ȡ�ļĴ�����ַ
	for(i=0;i<DateLen;i++) //��ȡ����
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
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
//����ģʽ
void NRFSetRXMode()
{
    CE=0;
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);                 // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
	NRFWriteReg(W_REGISTER+CONFIG,0x0f);             // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ     
  	CE = 1; 
	delay_ms(5);    
}
				
void GetDate()				 
{		 
	sta=NRFReadReg(R_REGISTER+STATUS);//�������ݺ��ȡ״̬�Ĵ���
	 if(RX_DR)				// �ж��Ƿ���յ�����
	 {		 
	 CE=0;//����
 	 NRFReadRxDate(R_RX_PAYLOAD,RevTempDate,RX_DATA_WITDH);// ��RXFIFO��ȡ���� ����4λ���ɣ���һλλ����λ
	 NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�
	 CSN=0;
	 NRFSPI(FLUSH_RX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
	 CSN=1;	 
	 }  
} 					 