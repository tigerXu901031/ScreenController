#include "../drv/STC8.H"
#include "../app/ParaDefine.H"

#include "intrins.h"
#include "../drv/19296p1.c"
#include "../drv/uartDrv.h"
#include "task.h"

#define  time_ms 400 

//sbit LED1 = P3^6;
//sbit LED2 = P3^5;
//sbit Key1 = P3^2;
//sbit Key2 = P3^3;

typedef struct{
	uint I_current;
	uchar I_Digit1;
	uchar I_Digit2;
	uchar I_Digit3;
	uchar I_Digit4;
	uchar I_Digit5;
//	uchar I_DotPosition;
		
	uint F_frequency;
	uchar F_Digit1;
	uchar F_Digit2;
	uchar F_Digit3;
	uchar F_Digit4;
	uchar F_Digit5;
//	uchar F_DotPosition;
	
	uint E_encoder;
	uchar E_Digit1;
	uchar E_Digit2;
	uchar E_Digit3;
	uchar E_Digit4;
	uchar E_Digit5;
	
	uint RT_runtime;
	uchar RT_Digit1;
	uchar RT_Digit2;
	uchar RT_Digit3;
	uchar RT_Digit4;
	uchar RT_Digit5;
	
	uchar Motor_Direction;
	uchar Motor_Direction_Set;
	
	uchar Up_Limit_Set;
	uchar Low_Limit_Set;
}Machine_Parameters_Def;

Machine_Parameters_Def Motor_Parameter;
uchar char_num[16];
uchar count=0;
uint Timer4_Count;


void Display_Full_Line_Up(uchar x);
void Display_Full_Line_Down(uchar x);

void Disp_Page_00_00(void);
void Disp_Page_00_01(void);
void Disp_Page_00_02(void);
void Disp_Page_00_03(void);

void Disp_Page_01_00(void);
void Disp_Page_01_01(void);
void Disp_Page_01_02(void);
void Disp_Page_01_03(void);

void Display_Page00_00_ParaArea(void);
void Display_Page00_01_ParaArea(void);
void Display_Page00_03_ParaArea(void);

void Display_Encoder_Number(void);
void Display_Encoder_Number1(void);
void Display_I_current(void);
void Display_F_frequency(void);
void Display_RunTime(void);

void BUTTON1_Display1_FanXiang(void);
void BUTTON1_Display1_ZhengXiang(void);
void BUTTON1_Display2_Fanhui(void);


void BUTTON2_Display1_QueRen(void);
void BUTTON2_Display2_Fanhui(void);
void BUTTON2_Display3_Caidan(void);


void Display_Page00_00_MotorDirt(void);
void Display_Page00_01_LLStudy(void);
void Display_Page00_03_ZDKJ(void);


void Motor_Direction_Update(void);

void Number_Lookup_Table(uchar number);
void Display_Full_Vertical_Line(uchar line);


//���ܣ���ʱ�ӳ���  ������time  Ϊ����ms��
void delay_ms(unsigned int time)
{
	 unsigned int  i;
	 unsigned int  j;
	 for(i=0;i<time;i++)
		for(j=0;j<1668;j++);
}

//���ܣ�IO��ʼ��  ��������
void IO_INIT()
{
	//��ע��I/O�ڸ��ֲ�ͬ�Ĺ���ģʽ�����ý��ܼ� STC15 ϵ���ĵ���400ҳ	
//	P3M0 = 0XFF;
//	P3M1 = 0X00;			//P3������Ϊ�������(ǿ����������ɴ�20mA)
//  P3 = 0X00;										//�ϵ��IO��ʼ��Ϊ�͵�ƽ	
//	P3M0 = 0x10;	//0001 0000
//	P3M1 = 0x00;	//0000 0000
//	P3PU |= 0x08;	//0000 1000
}

void Display_Full_Line_Up(uchar x)
{
	uchar i;
//	if(x==2)
//		{
//			for(i=1;i<15;i++)
//				{display_8x8((i-1)*8+1,x,Char0808_Up);}
//			display_8x8(185,x,Char0808_Up);
//		}
//		else
//			{
				for(i=1;i<25;i++)
				{display_8x8((i-1)*8+1,x,Char0808_Up);}
//			}
}

void Display_Full_Line_Down(uchar x)
{
	uchar i;
	if(x==12)
		{
			//������һ��
			display_8x8(1,12,Char0808_Down);
			for(i=2;i<6;i++)
				{display_8x8((i-1)*8+1,12,Char0808_UpDown);}
			for(i=6;i<20;i++)
				{display_8x8((i-1)*8+1,12,Char0808_Down);}			
			for(i=20;i<24;i++)
				{display_8x8((i-1)*8+1,12,Char0808_UpDown);}
			display_8x8(185,12,Char0808_Down);
		}
		else
			{
				for(i=1;i<25;i++)
				{display_8x8((i-1)*8+1,x,Char0808_Down);}
			}
}

void Display_Full_Vertical_Line(uchar line)
{
	uchar i;
	for(i=1;i<13;i++)
		{display_8x1(line,i,0xFF);}
}

void BUTTON1_Display1_FanXiang(void)		//����
{
	uchar i;
	for(i=2;i<6;i++)
	{display_8x8((i-1)*8+1,9,Char0808_Down);}
	Hanzi_Disp_16x16(9, 10, Hanzi_1616_XST_Fan1, 0x04);	//0000 0100
	Hanzi_Disp_16x16(25, 10, Hanzi_1616_XST_Xiang, 0x08); //00001000
	for(i=2;i<6;i++)
	{display_8x8((i-1)*8+1, 12,Char0808_Up);}
	Display_Full_Line_Down(12); 
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192); 
}

void BUTTON1_Display1_ZhengXiang(void)		//����
{
	uchar i;
	for(i=2;i<6;i++)
	{display_8x8((i-1)*8+1,9,Char0808_Down);}
	Hanzi_Disp_16x16(9, 10, Hanzi_1616_XST_Zheng, 0x04);	//0000 0100
	Hanzi_Disp_16x16(25, 10, Hanzi_1616_XST_Xiang, 0x08); //00001000
	for(i=2;i<6;i++)
	{display_8x8((i-1)*8+1, 12,Char0808_Up);}
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
}

void BUTTON1_Display2_Fanhui(void)		//����
{
	uchar i;
	for(i=2;i<6;i++)
	{display_8x8((i-1)*8+1,9,Char0808_Down);}
	Hanzi_Disp_16x16(9, 10, Hanzi_1616_XST_Fan, 0x04);	//0000 0100
	Hanzi_Disp_16x16(25, 10, Hanzi_1616_XST_Hui, 0x08); //00001000
	for(i=2;i<6;i++)
	{display_8x8((i-1)*8+1, 12,Char0808_Up);}
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
}

void BUTTON1_Display3_Caidan(void)		//�˵�
{
	uchar i;
	for(i=2;i<6;i++)
	{display_8x8((i-1)*8+1,9,Char0808_Down);}
	Hanzi_Disp_16x16(9, 10, Hanzi_1616_XST_Cai, 0x04);	//0000 0100
	Hanzi_Disp_16x16(25, 10, Hanzi_1616_XST_Dan, 0x08); //00001000
	for(i=2;i<6;i++)
	{display_8x8((i-1)*8+1, 12,Char0808_Up);}
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
}

void BUTTON2_Display1_QueRen(void)		//ȷ��
{
	uchar i;
	for(i=20;i<24;i++)
	{display_8x8((i-1)*8+1,9,Char0808_Down);}
	Hanzi_Disp_16x16(153, 10, Hanzi_1616_XST_Que, 0x04);	//0000 0100
	Hanzi_Disp_16x16(169, 10, Hanzi_1616_XST_Ren, 0x08); //00001000
	for(i=20;i<24;i++)
	{display_8x8((i-1)*8+1, 12,Char0808_Up);}
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
}

void BUTTON2_Display2_Fanhui(void)		//����
{
	uchar i;
	for(i=20;i<24;i++)
	{display_8x8((i-1)*8+1,9,Char0808_Down);}
	Hanzi_Disp_16x16(153, 10, Hanzi_1616_XST_Fan, 0x04);	//0000 0100
	Hanzi_Disp_16x16(169, 10, Hanzi_1616_XST_Hui, 0x08); //00001000
	for(i=20;i<24;i++)
	{display_8x8((i-1)*8+1, 12,Char0808_Up);}
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
}

void BUTTON2_Display3_Caidan(void)		//�˵�
{
	uchar i;
	for(i=20;i<24;i++)
	{display_8x8((i-1)*8+1,9,Char0808_Down);}
	Hanzi_Disp_16x16(153, 10, Hanzi_1616_XST_Cai, 0x04);	//0000 0100
	Hanzi_Disp_16x16(169, 10, Hanzi_1616_XST_Dan, 0x08); //00001000
	for(i=20;i<24;i++)
	{display_8x8((i-1)*8+1, 12,Char0808_Up);}
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
}

void Number_Lookup_Table(uchar number)
{
		uchar i;
		for(i=0;i<16;i++)
		{char_num[i] = char_number_table[number*16+i];}
}

void Display_Encoder_Number(void)
{
	uint encoder;
	encoder = Motor_Parameter.E_encoder;
	
	if(encoder>10000)			//���λ
		{
			Motor_Parameter.E_Digit1 = encoder/10000;
			encoder %= 10000;	
		}
		else {Motor_Parameter.E_Digit1 = 0;}
		
	if(encoder>1000)		//��2λ
		{
			Motor_Parameter.E_Digit2 = encoder/1000;
			encoder %= 1000;	
		}
		else {Motor_Parameter.E_Digit2 = 0;}
		
	if(encoder>100)		//��3λ
		{
			Motor_Parameter.E_Digit3 = encoder/100;
			encoder %= 100;	
		}
		else {Motor_Parameter.E_Digit3 = 0;}
		
	if(encoder>10)		//��4λ
		{
			Motor_Parameter.E_Digit4 = encoder/10;
			encoder %= 10;	
		}
		else {Motor_Parameter.E_Digit4 = 0;}
			
	Motor_Parameter.E_Digit5 = encoder;		//��5λ
	
	Number_Lookup_Table(Motor_Parameter.E_Digit1);
	CHAR_Display_16x8(57, 2,char_num, 0); 

	Number_Lookup_Table(Motor_Parameter.E_Digit2);
	CHAR_Display_16x8(65, 2,char_num, 0); 

	Number_Lookup_Table(Motor_Parameter.E_Digit3);
	CHAR_Display_16x8(73, 2,char_num, 0); 

	Number_Lookup_Table(Motor_Parameter.E_Digit4);
	CHAR_Display_16x8(81, 2,char_num, 0); 

	Number_Lookup_Table(Motor_Parameter.E_Digit5);
	CHAR_Display_16x8(89, 2,char_num, 0); 
}

void Display_Encoder_Number1(void)
{
	uint encoder;
	encoder = Motor_Parameter.E_encoder;
	
	if(encoder>10000)			//���λ
		{
			Motor_Parameter.E_Digit1 = encoder/10000;
			encoder %= 10000;	
		}
		else {Motor_Parameter.E_Digit1 = 0;}
		
	if(encoder>1000)		//��2λ
		{
			Motor_Parameter.E_Digit2 = encoder/1000;
			encoder %= 1000;	
		}
		else {Motor_Parameter.E_Digit2 = 0;}
		
	if(encoder>100)		//��3λ
		{
			Motor_Parameter.E_Digit3 = encoder/100;
			encoder %= 100;	
		}
		else {Motor_Parameter.E_Digit3 = 0;}
		
	if(encoder>10)		//��4λ
		{
			Motor_Parameter.E_Digit4 = encoder/10;
			encoder %= 10;	
		}
		else {Motor_Parameter.E_Digit4 = 0;}
			
	Motor_Parameter.E_Digit5 = encoder;		//��5λ
	
	Number_Lookup_Table(Motor_Parameter.E_Digit1);
	CHAR_Display_16x8(57, 1,char_num, 1); 

	Number_Lookup_Table(Motor_Parameter.E_Digit2);
	CHAR_Display_16x8(65, 1,char_num, 1); 

	Number_Lookup_Table(Motor_Parameter.E_Digit3);
	CHAR_Display_16x8(73, 1,char_num, 1); 

	Number_Lookup_Table(Motor_Parameter.E_Digit4);
	CHAR_Display_16x8(81, 1,char_num, 1); 

	Number_Lookup_Table(Motor_Parameter.E_Digit5);
	CHAR_Display_16x8(89, 1,char_num, 1); 
}


void Display_RunTime(void)
{
	uint runtime;
	runtime = Motor_Parameter.RT_runtime;
	
	if(runtime>10000)			//���λ
		{
			Motor_Parameter.RT_Digit1 = runtime/10000;
			runtime %= 10000;	
		}
		else {Motor_Parameter.RT_Digit1 = 0;}
		
	if(runtime>1000)		//��2λ
		{
			Motor_Parameter.RT_Digit2 = runtime/1000;
			runtime %= 1000;	
		}
		else {Motor_Parameter.RT_Digit2 = 0;}
		
	if(runtime>100)		//��3λ
		{
			Motor_Parameter.RT_Digit3 = runtime/100;
			runtime %= 100;	
		}
		else {Motor_Parameter.RT_Digit3 = 0;}
		
	if(runtime>10)		//��4λ
		{
			Motor_Parameter.RT_Digit4 = runtime/10;
			runtime %= 10;	
		}
		else {Motor_Parameter.RT_Digit4 = 0;}
			
	Motor_Parameter.RT_Digit5 = runtime;		//��5λ
	
	Number_Lookup_Table(Motor_Parameter.RT_Digit1);
	CHAR_Display_16x8(57, 3,char_num, 0); 

	Number_Lookup_Table(Motor_Parameter.RT_Digit2);
	CHAR_Display_16x8(65, 3,char_num, 0); 

	Number_Lookup_Table(Motor_Parameter.RT_Digit3);
	CHAR_Display_16x8(73, 3,char_num, 0); 

	Number_Lookup_Table(Motor_Parameter.RT_Digit4);
	CHAR_Display_16x8(81, 3,char_num, 0); 

	Number_Lookup_Table(Motor_Parameter.RT_Digit5);
	CHAR_Display_16x8(89, 3,char_num, 0); 		
}

void Display_I_current(void)
{
	uint current_data;
	current_data = Motor_Parameter.I_current;

	if(current_data>10000)			//���λ
		{
			Motor_Parameter.I_Digit1 = current_data/10000;
			current_data %= 10000;	
		}
		else {Motor_Parameter.I_Digit1 = 0;}
		
	if(current_data>1000)		//��2λ
		{
			Motor_Parameter.I_Digit2 = current_data/1000;
			current_data %= 1000;	
		}
		else {Motor_Parameter.I_Digit2 = 0;}
		
	if(current_data>100)		//��3λ
		{
			Motor_Parameter.I_Digit3 = current_data/100;
			current_data %= 100;	
		}
		else {Motor_Parameter.I_Digit3 = 0;}
		
	if(current_data>10)		//��4λ
		{
			Motor_Parameter.I_Digit4 = current_data/10;
			current_data %= 10;	
		}
		else {Motor_Parameter.I_Digit4 = 0;}
			
	Motor_Parameter.I_Digit5 = current_data;		//��5λ
	
	Number_Lookup_Table(Motor_Parameter.I_Digit1);
	CHAR_Display_16x8(129, 1,char_num, 1); 			//���Ϻ�

	Number_Lookup_Table(Motor_Parameter.I_Digit2);
	CHAR_Display_16x8(137, 1,char_num, 1); 			//���Ϻ� 

	Number_Lookup_Table(Motor_Parameter.I_Digit3);
	CHAR_Display_16x8(145, 1,char_num, 1); 			//���Ϻ� 

	Number_Lookup_Table(Motor_Parameter.I_Digit4);
	CHAR_Display_16x8(161, 1,char_num, 1); 			//���Ϻ� 

	Number_Lookup_Table(Motor_Parameter.I_Digit5);
	CHAR_Display_16x8(169, 1,char_num, 1); 			//���Ϻ� 
}

void Display_F_frequency(void)
{
	uint frequency_data;
	frequency_data = Motor_Parameter.F_frequency;

	if(frequency_data>10000)			//���λ
		{
			Motor_Parameter.F_Digit1 = frequency_data/10000;
			frequency_data %= 10000;	
		}
		else {Motor_Parameter.F_Digit1 = 0;}
		
	if(frequency_data>1000)		//��2λ
		{
			Motor_Parameter.F_Digit2 = frequency_data/1000;
			frequency_data %= 1000;	
		}
		else {Motor_Parameter.F_Digit2 = 0;}
		
	if(frequency_data>100)		//��3λ
		{
			Motor_Parameter.F_Digit3 = frequency_data/100;
			frequency_data %= 100;	
		}
		else {Motor_Parameter.F_Digit3 = 0;}
		
	if(frequency_data>10)		//��4λ
		{
			Motor_Parameter.F_Digit4 = frequency_data/10;
			frequency_data %= 10;	
		}
		else {Motor_Parameter.F_Digit4 = 0;}
			
	Motor_Parameter.F_Digit5 = frequency_data;		//��5λ
	
	Number_Lookup_Table(Motor_Parameter.F_Digit1);
	CHAR_Display_16x8(129, 3,char_num, 0); 			//���Ϻ�

	Number_Lookup_Table(Motor_Parameter.F_Digit2);
	CHAR_Display_16x8(137, 3,char_num, 0); 			//���Ϻ� 

	Number_Lookup_Table(Motor_Parameter.F_Digit3);
	CHAR_Display_16x8(145, 3,char_num, 0); 			//���Ϻ� 

	Number_Lookup_Table(Motor_Parameter.F_Digit4);
	CHAR_Display_16x8(161, 3,char_num, 0); 			//���Ϻ� 

	Number_Lookup_Table(Motor_Parameter.F_Digit5);
	CHAR_Display_16x8(169, 3,char_num, 0); 			//���Ϻ� 
}

void Motor_Direction_Update(void)
{
	if(Motor_Parameter.Motor_Direction == 1)
		{BUTTON1_Display1_ZhengXiang();	}
		else
			{	BUTTON1_Display1_FanXiang();}
}

void Display_Page00_00_ParaArea(void)		//Page00_00���������
{
	Hanzi_Disp_16x16(1, 2, Hanzi_1616_XST_Bian, 0x04);	//0000 0100
	Hanzi_Disp_16x16(17, 2, Hanzi_1616_XST_Ma, 0);	//0000 0100
	Hanzi_Disp_16x16(33, 2, Hanzi_1616_XST_Qi, 0);	//0000 0100
	CHAR_Display_16x8(49,2,char_cMaohao, 0);
	Display_Encoder_Number();
}

void Display_Page00_01_ParaArea(void)		//Page00_01���������
{
	Display_Page00_00_ParaArea();
	CHAR_Display_16x8(113,1,char_capital_I, 1);
	CHAR_Display_16x8(121,1,char_cMaohao, 1);
	CHAR_Display_16x8(153,1,char_cDot, 1);
	CHAR_Display_16x8(113,3,char_capital_F, 0);
	CHAR_Display_16x8(121,3,char_cMaohao, 0);
	CHAR_Display_16x8(153,3,char_cDot, 0);
	CHAR_Display_16x8(177,1,char_capital_A, 1);
	CHAR_Display_16x8(177,3,char_capital_H, 0);
	CHAR_Display_16x8(185,3,char_z, 0);
	Display_I_current();
	Display_F_frequency();
}

void Display_Page00_03_ParaArea(void)	//��ʾ�̶���Ϣ
{
	Hanzi_Disp_16x16(1, 1, Hanzi_1616_XST_Bian, 1);	
	Hanzi_Disp_16x16(17, 1, Hanzi_1616_XST_Ma, 1);	
	Hanzi_Disp_16x16(33, 1, Hanzi_1616_XST_Qi, 1);	
	CHAR_Display_16x8(49,1,char_cMaohao, 1);
	Hanzi_Disp_16x16(1, 3, Hanzi_1616_XST_Yun, 0);	
	Hanzi_Disp_16x16(17, 3, Hanzi_1616_XST_Xing, 0);	
	Hanzi_Disp_16x16(33, 3, Hanzi_1616_XST_Shu, 0);	
	CHAR_Display_16x8(49,3,char_cMaohao, 0);
	
	CHAR_Display_16x8(113,1,char_capital_I, 1);
	CHAR_Display_16x8(121,1,char_cMaohao, 1);
	CHAR_Display_16x8(153,1,char_cDot, 1);
	CHAR_Display_16x8(177,1,char_capital_A, 1);
	CHAR_Display_16x8(113,3,char_capital_F, 0);
	CHAR_Display_16x8(121,3,char_cMaohao, 0);
	CHAR_Display_16x8(153,3,char_cDot, 0);
	CHAR_Display_16x8(177,3,char_capital_H, 0);
	CHAR_Display_16x8(185,3,char_z, 0);
	
	Display_Encoder_Number1();
	Display_RunTime();
	Display_I_current();
	Display_F_frequency();
}

void Display_Page00_00_MotorDirt(void)	//�������
{
	disp_24x24(49,6,Hanzi_2424_HWZS_Dian);
	disp_24x24(73,6,Hanzi_2424_HWZS_Ji);
	disp_24x24(97,6,Hanzi_2424_HWZS_Fang);
	disp_24x24(121,6,Hanzi_2424_HWZS_Xiang);
//	disp_96x24(49,6,Hanzi_9624_HWZS_DJFX);
}

void Display_Page00_01_LLStudy(void)		//����λѧϰ
{
	disp_24x24(33,6,Hanzi_2424_HWZS_Xia);
	disp_24x24(57,6,Hanzi_2424_HWZS_Xian);
	disp_24x24(81,6,Hanzi_2424_HWZS_Wei);
	disp_24x24(105,6,Hanzi_2424_HWZS_Xue);
	disp_24x24(129,6,Hanzi_2424_HWZS_Xi);
//	disp_96x24(49,6,Hanzi_9624_HWZS_DJFX);
}

void Display_Page00_01_ULStudy(void)		//����λѧϰ
{
	disp_24x24(33,6,Hanzi_2424_HWZS_Shang);
	disp_24x24(57,6,Hanzi_2424_HWZS_Xian);
	disp_24x24(81,6,Hanzi_2424_HWZS_Wei);
	disp_24x24(105,6,Hanzi_2424_HWZS_Xue);
	disp_24x24(129,6,Hanzi_2424_HWZS_Xi);
//	disp_96x24(49,6,Hanzi_9624_HWZS_DJFX);
}

void Display_Page00_03_ZDKJ(void)			//�µ�Ƽ�
{
	disp_24x24(49,6,Hanzi_2424_HWZS_Zhi);
	disp_24x24(73,6,Hanzi_2424_HWZS_Dian);
	disp_24x24(97,6,Hanzi_2424_HWZS_Ke);
	disp_24x24(121,6,Hanzi_2424_HWZS_Ji1);
//	disp_96x24(49,6,Hanzi_9624_HWZS_DJFX);
}

void Disp_Page_00_00(void)		//�������
{
	Display_Full_Line_Up(1);
	Display_Full_Line_Up(5);

	Motor_Parameter.E_encoder = 00001;
	Display_Page00_00_ParaArea();	//��ʾ�̶���Ϣ
	

	BUTTON1_Display1_FanXiang();		//��ʾ������
	BUTTON2_Display1_QueRen();		//��ʾ��ȷ�ϡ�
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	
	Display_Page00_00_MotorDirt(); 
	
	Display_Full_Vertical_Line(192);
}

void Disp_Page_00_01(void)		//����λѧϰ
{
	Display_Full_Line_Up(1);
	Display_Full_Line_Up(5);
	
	Motor_Parameter.E_encoder = 11223;
	Motor_Parameter.I_current = 12345;
	Motor_Parameter.F_frequency = 62503;
	Display_Page00_01_ParaArea();	//��ʾ�̶���Ϣ
	
	BUTTON1_Display2_Fanhui();		//��ʾ�����ء�
	BUTTON2_Display1_QueRen();		//��ʾ��ȷ����
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
	
	Display_Page00_01_LLStudy();
	
}

void Disp_Page_00_02(void)		//����λѧϰ
{
	Display_Full_Line_Up(1);
	Display_Full_Line_Up(5);
	Motor_Parameter.E_encoder = 11223;
	Motor_Parameter.I_current = 12345;
	Motor_Parameter.F_frequency = 25389;
	Display_Page00_01_ParaArea();	//��ʾ�̶���Ϣ
	
	BUTTON1_Display2_Fanhui();		//��ʾ�����ء�
	BUTTON2_Display1_QueRen();		//��ʾ��ȷ����
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
	
	Display_Page00_01_ULStudy();
}

void Disp_Page_00_03(void)
{
	Display_Full_Line_Up(1);
	Display_Full_Line_Up(5);
	Motor_Parameter.E_encoder = 11223;
	Motor_Parameter.I_current = 12345;
	Motor_Parameter.F_frequency = 25389;
	Motor_Parameter.RT_runtime = 00002;
	
	Display_Page00_03_ParaArea();	//��ʾ�̶���Ϣ
	
//	BUTTON1_Display3_Caidan();		//��ʾ���˵���
//	BUTTON2_Display2_Fanhui();		//��ʾ�����ء�

	BUTTON1_Display2_Fanhui();		//��ʾ�����ء�
	BUTTON2_Display3_Caidan();		//��ʾ���˵���

	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
	Display_Page00_03_ZDKJ();
}


void Disp_Page_01_00(void)
{
	Display_Full_Line_Up(1);
	Display_Full_Line_Up(5);
	
	Display_Page00_01_ParaArea();	//��ʾ�̶���Ϣ
	
	BUTTON1_Display2_Fanhui();		//��ʾ�����ء�
	BUTTON2_Display1_QueRen();		//��ʾ��ȷ����
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
	
	
	
}

void Disp_Page_01_01(void)
{
	Display_Full_Line_Up(1);
	Display_Full_Line_Up(5);
	
	Display_Page00_01_ParaArea();	//��ʾ�̶���Ϣ
	
	BUTTON1_Display2_Fanhui();		//��ʾ�����ء�
	BUTTON2_Display1_QueRen();		//��ʾ��ȷ����
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
	

}

void Disp_Page_01_02(void)
{
	Display_Full_Line_Up(1);
	Display_Full_Line_Up(5);
	
	Display_Page00_01_ParaArea();	//��ʾ�̶���Ϣ
	
	BUTTON1_Display2_Fanhui();		//��ʾ�����ء�
	BUTTON2_Display1_QueRen();		//��ʾ��ȷ����
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
	
	
	
}

void Disp_Page_01_03(void)
{
	Display_Full_Line_Up(1);
	Display_Full_Line_Up(5);
	
	Display_Page00_01_ParaArea();	//��ʾ�̶���Ϣ
	
	BUTTON1_Display2_Fanhui();		//��ʾ�����ء�
	BUTTON2_Display1_QueRen();		//��ʾ��ȷ����
	Display_Full_Line_Down(12);
	Display_Full_Vertical_Line(1);
	Display_Full_Vertical_Line(192);
	
		
}

void LCD_Diaplay_Page(uchar page, uchar level)
{
	clear_screen();
	if(page == 0)
		{
			switch(level)
			{
				case 0:	Disp_Page_00_00();break;
				case 1:	Disp_Page_00_01();break;
				case 2:	Disp_Page_00_02();break;
				case 3:	Disp_Page_00_03();break;
				default: break;
			}
		}
		else
			{;}
	if(page == 1)
		{
			switch(level)
			{
				case 0:	Disp_Page_01_00();break;
				case 1:	Disp_Page_01_01();break;
				case 2:	Disp_Page_01_02();break;
				case 3:	Disp_Page_01_03();break;
				default: break;
			}
		}
		else
			{;}
}

// void UartInit(void)		//9600bps@24.000MHz
// {
// 	//UART 1
// 	SCON	= 0x50;		//8λ����,�ɱ䲨����
// 	AUXR	|= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
// 	AUXR	&= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
// 	TMOD	&= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
// 	TL1		= 0x8F;		//�趨��ʱ��"background: #ffffff"ֵ
// 	TH1		= 0xFD;		//�趨��ʱ��ֵ
// 	ET1		= 0;		//��ֹ��ʱ��1�ж�
// 	TR1		= 1;		//������ʱ��1
// 	ES		= 1;                  /*�򿪴����ж�*/
	
// 	//UART 2
// 	//reserved
	
// 	//UART 3 Baud Rate:9600, using Timer3
// 	S3CON = 	0x10;		//8λ����,�ɱ䲨����
// 	S3CON |= 	0x40;		//����3ѡ��ʱ��3Ϊ�����ʷ�����
// 	T4T3M &= 	0xFD;		//��ʱ��3ʱ��ΪFosc/12,��12T
// 	T3L 	= 	0xCC;		//�趨��ʱ��ֵ
// 	T3H 	= 	0xFF;		//�趨��ʱ��ֵ
// 	T4T3M |= 	0x08;		//������ʱ��3
	
// 	//UART 4					Baud Rate:9600, using Timer2
// 	S4CON = 	0x10;		//8λ����,�ɱ䲨����
// 	S4CON &= 	0xBF;		//����4ѡ��ʱ��2Ϊ�����ʷ�����
// 	AUXR 	&= 	0xFB;		//��ʱ��2ʱ��ΪFosc/12,��12T
// 	T2L 	= 	0xCC;		//�趨��ʱ��ֵ
// 	T2H 	= 	0xFF;		//�趨��ʱ��ֵ
// 	AUXR 	|= 	0x10;		//������ʱ��2
		
// 	EA		= 1;                  /*�����ж�*/
// }

// void Timer7Init(void)		//10����@24.000MHz
// {
// //	T4T3M &= 0xDF;		//��ʱ��ʱ��12Tģʽ 0b11011111
// 	T4T3M &= 0x0F;		//��ʱ��ʱ��12Tģʽ, ��ʱ��ģʽ��ʱ������ر� 0b00001111
// 	T4L = 0xE0;		//���ö�ʱ��ֵ
// 	T4H = 0xB1;		//���ö�ʱ��ֵ
// //	T4T3M |= 0x80;		//��ʱ��4��ʼ��ʱ
// }

// void Timer10ms_Enable(void)
// {
// 	T4T3M |= 0x80;		//��ʱ��4��ʼ��ʱ
// 	IE2		|= ET4;			//0b01000000
// }

// void Timer10ms_Disable(void)
// {
// 	T4T3M &= 0x7F;		//��ʱ��4ֹͣ��ʱ
// 	IE2		&= ~ET4;		//0b10111111
// }


//������ ��������
void main()
{

	IO_INIT();										//IO��ʼ��
	// UartInit();
	INIT_LCD();
	// Timer7Init();									//T4 timer initialization
	delay_ms(200);								//�ϵ���ʱ100ms
	clear_screen();
	// Timer10ms_Enable();
//	Timer10ms_Disable();
	taskInit();
//	LED2 = 1;
//	disp_32x32(1,1,Hanzi_3232_XST_Xiang);
//	disp_16x16(1,4,Hanzi_1616_XST_Ding);
//	LCD_Diaplay_Page(0,1);
	
	Disp_Page_00_00();
	
	
	
	while(1)											//��ѭ��
	{
		delay_ms(200);
		uartDrvUpdate();
	}
}

// void UART_SER (void) interrupt 4 //�����жϷ������
// {
//     unsigned char Temp, temp2;          //������ʱ���� 
   
//    if(RI)                        //�ж��ǽ����жϲ���
//     {
// 	  	RI=0;                      //��־λ����
// 	  	Temp = SBUF;                 //���뻺������ֵ

// 	  	if(Temp == 0x30)
// 	  		{
// 	  			LCD_Diaplay_Page(0,count);
// 	  			count++;
// 	  			if(count>3)
// 	  				{count = 0;}
// 	  				else {;}
// 	  		}

// 	  	if((Temp & 0xF0) == 0x40)		//0100 0000
// 	  		{
// 	    	  temp2 = (Temp & 0x0F);
// 	    	  LCD_Diaplay_Page(1,temp2);
// 	  		}          
// 			if(Temp == 0x50)
// 				{
// 					Motor_Parameter.Motor_Direction = 0;
// 					Motor_Direction_Update();
// 				}
// 			if(Temp == 0x51)
// 				{
// 					Motor_Parameter.Motor_Direction = 1;
// 					Motor_Direction_Update();
// 				}

// 	 }
//    if(TI)                        //����Ƿ��ͱ�־λ������
//      TI=0;
// }



// void Timer4(void) interrupt 20
// {
// 	uchar i;
// 	Timer4_Count++;
// 	T4L = 0xE0;		//���ö�ʱ��ֵ
// 	T4H = 0xB1;		//���ö�ʱ��ֵ
// 	AUXINTIF &= ~T4IF;	//clear T4IF flag
// 	TR0 = 1;
// }

// void UART3_SER (void) interrupt 17 // UART 3 interrupt function
// {
//     uchar Temp;          						//Define temporay variant 
   
//    if(S3CON&S3RI)                        	//Receive interrupt
//     {
// 	  	Temp = S3BUF;                 //read in the data in S3BUF
// 			S3BUF = Temp;									//send back to master for testing
// 	 }
//    if(S3CON&S3TI)                        	
//      S3CON &= ~S3TI;
// }


// void UART4_SER (void) interrupt 18 // UART 4 interrupt function
// {
//     uchar Temp;          						//Define temporay variant 
   
//    if(S4CON&S4RI)                        	//Receive interrupt
//     {	
// 	  	Temp = S4BUF;                 //read in the data in S3BUF
// 			S4BUF = Temp;									//send back to master for testing
// 	 }
//    if(S4CON&S4TI)                        
//      S4CON &= ~S4TI;
// }
