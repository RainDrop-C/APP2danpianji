
#define uint unsigned int
#define uchar unsigned char

void write_com(uchar com);//дָ��
void write_date(uchar date); //д����
void init_12864(void);
void display_string(unsigned char x,unsigned char y,unsigned char *s);//yΪ��xΪ��
void display_distance1(uchar x,uchar y,uint num2);
void display_distance2(uchar x,uchar y,uint num1); //��ʾ����