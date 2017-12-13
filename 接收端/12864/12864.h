
#define uint unsigned int
#define uchar unsigned char

void write_com(uchar com);//写指令
void write_date(uchar date); //写数据
void init_12864(void);
void display_string(unsigned char x,unsigned char y,unsigned char *s);//y为行x为列
void display_distance1(uchar x,uchar y,uint num2);
void display_distance2(uchar x,uchar y,uint num1); //显示距离