/*****HMI.H******/

#ifndef __HMI_H_
#define __HMI_H_

#define uchar unsigned char
#define uint unsigned int

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




//汉字取模设置：阴码，列行式，顺向
extern uchar code Hanzi_1616_ST_Dian[],Hanzi_1616_ST_Ji[],Hanzi_1616_HWXH_Dian[],Hanzi_1616_HWXH_Ji[],Hanzi_1616_XST_Fan[],Hanzi_1616_XST_Hui[];
extern uchar code Hanzi_1616_XST_Que[],Hanzi_1616_XST_Ding[],Hanzi_1616_XST_Ren[],Hanzi_1616_XST_Fan1[];
extern uchar code Hanzi_1616_XST_Zheng[],Hanzi_1616_XST_Xiang[],Hanzi_1616_XST_Bian[],Hanzi_1616_XST_Ma[],Hanzi_1616_XST_Qi[];
extern uchar code Hanzi_1616_XST_Yun[],Hanzi_1616_XST_Xing[],Hanzi_1616_XST_Shu[],Hanzi_1616_XST_Cai[],Hanzi_1616_XST_Dan[];
extern uchar code char_number_table[],char_cMaohao[],char_cDot[],char_capital_A[],char_capital_H[],char_capital_I[],char_capital_F[],char_z[];
extern uchar code Hanzi_2424_HWZS_Dian[],Hanzi_2424_HWZS_Ji[],Hanzi_2424_HWZS_Fang[],Hanzi_2424_HWZS_Xiang[],Hanzi_2424_HWZS_Xia[],Hanzi_2424_HWZS_Xian[];
extern uchar code Hanzi_2424_HWZS_Wei[],Hanzi_2424_HWZS_Xue[],Hanzi_2424_HWZS_Xi[],Hanzi_2424_HWZS_Shang[],Hanzi_2424_HWZS_Zhi[],Hanzi_2424_HWZS_Ke[];
extern uchar code Hanzi_2424_HWZS_Ji1[];




/////////////////////////////////////////////////

#endif