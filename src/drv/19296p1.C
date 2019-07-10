/* Һ��ģ���ͺţ�JLX19296-380
���нӿ�
����IC ��:ST75256
�ıࣺBruce Dong
2019.5.15
*/
#include "../drv/STC8.H"
#include "../drv/19296p1.H"
//#include "../app/HMI.H"

//Development Board Connection
//sbit LCD19296_CS1 = P3^7; 
//sbit LCD19296_RST = P3^6; 
//sbit LCD19296_RS = P3^5; 
//sbit LCD19296_RD = P3^4; 
//sbit LCD19296_WR = P0^7; 

//V1 temporary connection
sbit LCD19296_IF0	= P4^1;
sbit LCD19296_CS1 = P3^7; 
sbit LCD19296_RST = P2^0; 
sbit LCD19296_RS = P3^6; 
sbit LCD19296_RD = P5^1; 
sbit LCD19296_WR = P5^0; 

//V2 connection
//sbit LCD19296_CS1 = P4^1; 
//sbit LCD19296_RST = P5^0; 
//sbit LCD19296_RS = P3^7; 
//sbit LCD19296_RD = P3^6; 
//sbit LCD19296_WR = P5^1; 
//����P2.0~2.7 ��ӦDB0~DB7*/
//sbit key=P2^0; /*�����ӿڣ�P2.0 ����GND ֮���һ������*/

//extern uchar code Char1608_Up[], Char1608_Down[], Char1608_Left[], Char1608_Right[];
//extern uchar code Hanzi1616_Up[], Hanzi1616_Down[], Hanzi1616_Left[], Hanzi1616_Right[];
//
//extern uchar code Hanzi_2424_XST_Dian[], Hanzi_2424_XST_Ji[],Hanzi_2424_XST_Fang[], Hanzi_2424_XST_Xiang[];

/*��ʱ��1 �����i ��*/
void delay(int i)
{
	int j,k;
	for(j=0;j<i;j++)
	for(k=0;k<110;k++);
}
/*��ʱ��1us ��i ��*/
void delay_us(int i)
{
	int j,k;
	for(j=0;j<i;j++)
	for(k=0;k<1;k++);
}

//temporary send data function
void LCD_Send_PData(uchar data2send)
{
//	uchar temp1;
//	temp1 = data2send<<1;
//	P2 = temp1;
	if((data2send&0x80)==0)
		{P35 = 0;}		//D7
		else
			{P35 = 1;}
	if((data2send&0x40)==0)
		{P27 = 0;}
		else
			{P27 = 1;}
	if((data2send&0x20)==0)
		{P26 = 0;}
		else
			{P26 = 1;}
	if((data2send&0x10)==0)
		{P25 = 0;}
		else
			{P25 = 1;}
	if((data2send&0x08)==0)
		{P24 = 0;}
		else
			{P24 = 1;}
	if((data2send&0x04)==0)
		{P23 = 0;}
		else
			{P23 = 1;}
	if((data2send&0x02)==0)
		{P22 = 0;}
		else
			{P22 = 1;}
	if((data2send&0x01)==0)
		{P21 = 0;}
		else
			{P21 = 1;}
}




//=============transfer command to LCM===============
void SEND_CMD_LCD(uchar data1)
{
	LCD19296_CS1=0;
	LCD19296_RS=0;
	
	LCD19296_RD=0;
	delay_us(1);
	LCD19296_WR=0;
//	P2=data1;
	LCD_Send_PData(data1);
	LCD19296_RD=1;
	delay_us(1);
	LCD19296_CS1=1;
	LCD19296_RD=0;
}

//-----------transfer data to LCM---------------
void SEND_DATA_LCD(uchar data1)
{
	LCD19296_CS1=0;
	LCD19296_RS=1;
	LCD19296_RD=0;
	delay_us(1);
	LCD19296_WR=0;
//	P2=data1;
	LCD_Send_PData(data1);
	LCD19296_RD=1;
	delay_us(1);
	LCD19296_CS1=1;
	LCD19296_RD=0;
}

void INIT_LCD()
{
	LCD19296_IF0 = 0;
	LCD19296_RST=0;
	delay(100);
	LCD19296_RST=1;
	delay(100);
	SEND_CMD_LCD(0x30); //EXT=0
	SEND_CMD_LCD(0x94); //Sleep out
	SEND_CMD_LCD(0x31); //EXT=1
	SEND_CMD_LCD(0xD7); //Autoread disable
	SEND_DATA_LCD(0X9F); //
	SEND_CMD_LCD(0x32); //Analog SET
	SEND_DATA_LCD(0x00); //OSC Frequency adjustment
	SEND_DATA_LCD(0x01); //Frequency on booster capacitors->6KHz
	SEND_DATA_LCD(0x03); //Bias=1/11
	SEND_CMD_LCD(0x20); // Gray Level
	SEND_DATA_LCD(0x01);
	
	SEND_DATA_LCD(0x03);
	SEND_DATA_LCD(0x05);
	SEND_DATA_LCD(0x07);
	SEND_DATA_LCD(0x09);
	SEND_DATA_LCD(0x0b);
	SEND_DATA_LCD(0x0d);
	SEND_DATA_LCD(0x10);
	SEND_DATA_LCD(0x11);
	SEND_DATA_LCD(0x13);
	SEND_DATA_LCD(0x15);
	SEND_DATA_LCD(0x17);
	SEND_DATA_LCD(0x19);
	SEND_DATA_LCD(0x1b);
	SEND_DATA_LCD(0x1d);
	SEND_DATA_LCD(0x1f);
	SEND_CMD_LCD(0x30); //EXT=0
	SEND_CMD_LCD(0x75); //Page Address setting
	
	SEND_DATA_LCD(0X00); // XS=0
	SEND_DATA_LCD(0X14); // XE=159 0x28
	SEND_CMD_LCD(0x15); //Clumn Address setting
	SEND_DATA_LCD(0X00); // XS=0
	SEND_DATA_LCD(0Xff); // XE=256
	SEND_CMD_LCD(0xBC); //Data scan direction
	SEND_DATA_LCD(0x00); //MX.MY=Normal
	SEND_DATA_LCD(0xA6);
	SEND_CMD_LCD(0xCA); //Display Control
	SEND_DATA_LCD(0X00); //
	SEND_DATA_LCD(0X9F); //Duty=160
	SEND_DATA_LCD(0X20); //Nline=off
	SEND_CMD_LCD(0xF0); //Display Mode
	SEND_DATA_LCD(0X10); //10=Monochrome Mode,11=4Gray
	
	SEND_CMD_LCD(0x81); //EV control
//	SEND_DATA_LCD(0x3a); //VPR[5-0]
	SEND_DATA_LCD(0x30); //VPR[5-0]
	SEND_DATA_LCD(0x03); //�ֵ��Աȶ�
	SEND_CMD_LCD(0x20); //Power control
	SEND_DATA_LCD(0x0B); //D0=regulator ; D1=follower ; D3=booste, on:1 off:0
	delay_us(100);
	SEND_CMD_LCD(0xAF); //Display on
}

/*дLCD ���е�ַ��X Ϊ��ʼ���е�ַ��Y Ϊ��ʼ���е�ַ��x_total,y_total �ֱ�Ϊ�е�ַ���е�ַ����㵽�յ�Ĳ�ֵ */
void lcd_address(uchar x,uchar y,x_total,y_total)
{
	x=x-1;
	y=y+7;
	SEND_CMD_LCD(0x15); //Set Column Address
	SEND_DATA_LCD(x);
	SEND_DATA_LCD(x+x_total-1);
	SEND_CMD_LCD(0x75); //Set Page Address
	SEND_DATA_LCD(y);
	SEND_DATA_LCD(y+y_total-1);
	SEND_CMD_LCD(0x30);
	SEND_CMD_LCD(0x5c);
}

/* void lcd_address1(uchar x,uchar y,x_total,y_total)
{
	x=x-1;
	y=y+7;
	SEND_CMD_LCD(0x15); //Set Column Address
	SEND_DATA_LCD(x);
	SEND_DATA_LCD(x+x_total-1);
	SEND_CMD_LCD(0x75); //Set Page Address
	SEND_DATA_LCD(y);
	SEND_DATA_LCD(y+y_total-1);
	SEND_CMD_LCD(0x30);
	SEND_CMD_LCD(0x5c);
} */

/*дLCD ���е�ַ��X Ϊ��ʼ���е�ַ��Y Ϊ��ʼ���е�ַ��x_total,y_total �ֱ�Ϊ�е�ַ���е�ַ����㵽�յ�Ĳ�ֵ */
void SET_LCD_DISP_AREA(uchar Column, uchar Page, Column_Total,Page_Total)
{
	Column = Column - 1;
	Page = Page + 7;
	SEND_CMD_LCD(0x15); //Set Column Address
	SEND_DATA_LCD(Column);
	Column += Column_Total;
	Column -= 1;
	SEND_DATA_LCD(Column);
	SEND_CMD_LCD(0x75); //Set Page Address
	SEND_DATA_LCD(Page);
	Page += Page_Total;
	Page -= 1;
	SEND_DATA_LCD(Page);
	SEND_CMD_LCD(0x30);
	SEND_CMD_LCD(0x5c);
}

/*����*/
void clear_screen(void)
{
	uchar i,j;
	lcd_address(0,0,193,13);
	for(i=0;i<13;i++)
	{
		for(j=0;j<193;j++)
		{
			SEND_DATA_LCD(0x00);
		}
	}
}

void display_8x8(uchar column, uchar page,uchar *text) 
{ 
  uchar i; 
  lcd_address(column,page,8,1); 
    for(i=0;i<8;i++) 
    {
    	SEND_DATA_LCD(*text);
    	text++; 
    } 
}

void display_8x1(uchar column, uchar page,uchar text) 
{ 
  lcd_address(column,page,1,1); 
  SEND_DATA_LCD(text);
}

//void display_16x8(uchar column, uchar page,uchar *text) 
//{ 
//  uchar i; 
//  lcd_address(column,page,8,2); 
//    for(i=0;i<16;i++) 
//    {
//    	SEND_DATA_LCD(*text);
//    	text++; 
//    } 
//}

void CHAR_Display_16x8(uchar Column, uchar Page,uchar *dp, uchar Disp_Para) 
{ 
  uchar i, Char1608[16], *p1, *p2;
	SET_LCD_DISP_AREA(Column, Page, 8, 2); 
	
	p1 = Char1608;
	for(i=0;i<16;i++)
		{*(p1+i) = *(dp+i);}
	
//�ж��Ϻ�
	if((Disp_Para &	Disp_UP)>0)
		{
				p2 = Char1608_Up;
				for(i=0;i<16;i++)
				{*(p1+i)|=*(p2+i);}
		}
		else
			{;}

//�ж��º�
	if((Disp_Para &	Disp_Down)>0)
		{
				p2 = Char1608_Down;
				for(i=0;i<16;i++)
				{*(p1+i)|=*(p2+i);}
		}
		else
			{;}

//�ж�����
	if((Disp_Para &	Disp_Left)>0)
		{
				p2 = Char1608_Left;
				for(i=0;i<16;i++)
				{*(p1+i)|=*(p2+i);}
		}
		else
			{;}

//�ж�����
	if((Disp_Para &	Disp_Right)>0)
		{
				p2 = Char1608_Right;
				for(i=0;i<16;i++)
				{*(p1+i)|=*(p2+i);}
		}
		else
			{;}

    for(i=0;i<16;i++) 
    {
    	SEND_DATA_LCD(*(p1+i));
    } 
}

///*��ʾ16*16 ����ĺ��ֻ��ͬ��16*16 �����ͼ��*/
//void disp_16x16(uchar x,uchar y,uchar *dp)
//{
//	uchar i,j;
//	lcd_address(x,y,16,2);
//	for(i=0;i<2;i++)
//	{
//		for(j=0;j<16;j++)
//		{
//			SEND_DATA_LCD(*dp);
//			dp++;
//		}
//	}
//}

/*��ʾ16*16 ����ĺ���*/
/*�β�˵����bit0���Ϻ��ߣ�bit1���º��ߣ�bit2�������ߣ�bit3�������ߣ�bit4����꣬bit5������*/
/*	bit  7 6 5 4 3 2 1 0	*/
/*	Para x x x x x x x x	*/

void Hanzi_Disp_16x16(uchar Column, uchar Page, uchar *dp, uchar Disp_Para)
{
	uchar i, Hanzi1616[32], *p1, *p2;
	SET_LCD_DISP_AREA(Column, Page, 16, 2);

	p1 = Hanzi1616;
	for(i=0;i<32;i++)
		{*(p1+i) = *(dp+i);}
	
//�ж��Ϻ�
	if((Disp_Para &	Disp_UP)>0)
		{
				p2 = Hanzi1616_Up;
				for(i=0;i<32;i++)
				{*(p1+i)|=*(p2+i);}
		}
		else
			{;}

//�ж��º�
	if((Disp_Para &	Disp_Down)>0)
		{
				p2 = Hanzi1616_Down;
				for(i=0;i<32;i++)
				{*(p1+i)|=*(p2+i);}
		}
		else
			{;}

//�ж�����
	if((Disp_Para &	Disp_Left)>0)
		{
				p2 = Hanzi1616_Left;
				for(i=0;i<32;i++)
				{*(p1+i)|=*(p2+i);}
		}
		else
			{;}

//�ж�����
	if((Disp_Para &	Disp_Right)>0)
		{
				p2 = Hanzi1616_Right;
				for(i=0;i<32;i++)
				{*(p1+i)|=*(p2+i);}
		}
		else
			{;}

//������ʾ
	for(i=0;i<32;i++)
	{
		SEND_DATA_LCD(*(p1+i));
	}
}

/*��ʾ24*24 ����ĺ��ֻ��ͬ��24*24 �����ͼ��*/
void disp_24x24(int x,int y,uchar *dp)
{
	uchar i;
	lcd_address(x,y,24,3);
	for(i=0;i<72;i++)
	{
		SEND_DATA_LCD(*(dp+i));
	}
}

void disp_24x12(int x,int y,uchar *dp)
{
	uchar i;
	lcd_address(x,y,12,3);
	for(i=0;i<36;i++)
	{
		SEND_DATA_LCD(*(dp+i));
	}
}

/////*��ʾ32*32 ����ĺ��ֻ��ͬ��32*32 �����ͼ��*/
////void disp_32x32(int x,int y,uchar *dp)
////{
////	uchar i,j;
////	lcd_address(x,y,32,4);
////	for(i=0;i<4;i++)
////	{
////		for(j=0;j<32;j++)
////		{
////			SEND_DATA_LCD(*dp);
////			dp++;
////		}
////	}
////}
////
/////*��ʾ48*48 ����ĺ��ֻ�ͼ��*/
////void disp_48x48(uchar x,uchar y,char *dp)
////{
////	uchar i,j;
////	lcd_address(x,y,48,6);
////	for(i=0;i<6;i++)
////	{
////		for(j=0;j<48;j++)
////		{
////			SEND_DATA_LCD(*dp);
////			dp++;
////		}
////	}
////}
////
/////*��ʾ64*48 ����ĺ��ֻ�ͼ��*/
////void disp_64x48(uchar x,uchar y,char *dp)
////{
////	uchar i,j;
////	lcd_address(x,y,55,6);
////	for(i=0;i<6;i++)
////	{
////		for(j=0;j<55;j++)
////		{
////			SEND_DATA_LCD(*dp);
////			dp++;
////		}
////	}
////}
////
/////*��ʾ96*24 �����ͼ��*/
////void disp_96x24(uchar x,uchar y,char *dp)
////{
////	uchar i,j; 
////	lcd_address(x,y,96,3);
////	for(i=0;i<3;i++)
////	{
////		for(j=0;j<96;j++)
////		{
////			SEND_DATA_LCD(*dp);
////			dp++;
////		}
////	}
////}
////
/////*��ʾ196*96 �����ͼ��*/
////void disp_192x96(uchar x,uchar y,char *dp)
////{
////	uchar i,j; 
////	lcd_address(x,y,192,12);
////	for(i=0;i<12;i++)
////	{
////		for(j=0;j<192;j++)
////		{
////			SEND_DATA_LCD(*dp);
////			dp++;
////		}
////	}
////}

//������ţ�ȡ��ģ��ʽ�����룬����ʽ��˳��

uchar code Char0808_Up[]={0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80};/*"�Ϻ�"*/

uchar code Char0808_Down[]={0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};/*"�º�"*/

uchar code Char0808_Left[]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"����"*/

uchar code Char0808_Right[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF};/*"����"*/

uchar code Char0808_UpDown[]={0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81};/*"�Ϻ�+�º�"*/

uchar code Char1608_Up[]={
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"�Ϻ�"*/

uchar code Char1608_Down[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};/*"�º�"*/

uchar code Char1608_Left[]={
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"����"*/

uchar code Char1608_Right[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF};/*"����"*/

uchar code Hanzi1616_Up[]={
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"�Ϻ�"*/

uchar code Hanzi1616_Down[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};/*"�º�"*/

uchar code Hanzi1616_Left[]={
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"����"*/

uchar code Hanzi1616_Right[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF};/*"����"*/


