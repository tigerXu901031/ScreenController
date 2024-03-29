/*****HMI.H******/

#ifndef __HMI_H_
#define __HMI_H_

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define Up	1
#define Down	0

#define Hanzi_Zhengxiang 1
#define Hanzi_Fanxiang 2
#define Hanzi_Fanhui 3
#define Hanzi_Xuexi 4
#define Hanzi_Queren 5
#define Hanzi_Caidan 6

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
	
	ulong RT_runtime;
	uint  RT_runtimeL;
	uint  RT_runtimeH;
	uchar RT_Digit1;
	uchar RT_Digit2;
	uchar RT_Digit3;
	uchar RT_Digit4;
	uchar RT_Digit5;
	uchar RT_Digit6;
	uchar RT_Digit7;
	
	uchar Motor_Direction;
//	uchar Motor_Direction_Set;
	
	uchar Up_Limit_Set;
	uchar Low_Limit_Set;
}Machine_Parameters_Def;

extern Machine_Parameters_Def Motor_Parameter;


void Display_Full_Line(uchar ucLine, uchar ucUpDown);

void Disp_Page_MotorDirtSet(void);
void Disp_Page_DownLMT_STD(void);
void Disp_Page_UpLMT_STD(void);
void Disp_Page_CloseDoor_DelayT(void);
void Disp_Page_RunningMode(void);

void Disp_Page_01_00(void);
void Disp_Page_01_01(void);
void Disp_Page_01_02(void);
void Disp_Page_01_03(void);

void Display_Page00_00_ParaArea(void);
void Display_Page00_01_ParaArea(void);
void Display_Page00_03_ParaArea(void);

void Display_Page00_03_CDDT(void);
void Display_Page00_03_HMST(void);

extern void Display_Encoder_Number(uchar x);
extern void Display_I_current(void);
extern void Display_F_frequency(void);
extern void Display_RunTimeL(void);
extern void Display_RunTimeH(void);
extern void Display_ATMT(void);
extern void Disp_PWD_Nbr(void);

extern void Disp_Usr_PWD_Input(void);
extern void Disp_Usr_Pg(uchar Func, uchar F_Para);

void Display_Page00_00_MotorDirt(void);
void Display_Page00_01_LLStudy(void);
void Display_Page00_03_ZDKJ(void);

void Motor_Direction_Update(void);
void Display_InputCodeText(void);

void Number_Lookup_Table(uchar number);
void Display_Full_Vertical_Line(uchar line);
void BUTTON1_Display(uchar HanziButton);


//����ȡģ���ã����룬����ʽ��˳��
extern uchar code Hanzi_1616_ST_Dian[],Hanzi_1616_ST_Ji[],Hanzi_1616_HWXH_Dian[],Hanzi_1616_HWXH_Ji[],Hanzi_1616_XST_Fan[],Hanzi_1616_XST_Hui[];
extern uchar code Hanzi_1616_XST_Que[],Hanzi_1616_XST_Ding[],Hanzi_1616_XST_Ren[],Hanzi_1616_XST_Fan1[];
extern uchar code Hanzi_1616_XST_Zheng[],Hanzi_1616_XST_Xiang[],Hanzi_1616_XST_Bian[],Hanzi_1616_XST_Ma[],Hanzi_1616_XST_Qi[];
extern uchar code Hanzi_1616_XST_Yun[],Hanzi_1616_XST_Xing[],Hanzi_1616_XST_Shu[],Hanzi_1616_XST_Cai[],Hanzi_1616_XST_Dan[];
extern uchar code char_number_table[],char_cMaohao[],char_cDot[],char_capital_A[],char_capital_H[],char_capital_I[],char_capital_F[],char_z[];
extern uchar code Hanzi_2424_HWZS_Dian[],Hanzi_2424_HWZS_Ji[],Hanzi_2424_HWZS_Fang[],Hanzi_2424_HWZS_Xiang[],Hanzi_2424_HWZS_Xia[],Hanzi_2424_HWZS_Xian[];
extern uchar code Hanzi_2424_HWZS_Wei[],Hanzi_2424_HWZS_Xue[],Hanzi_2424_HWZS_Xi[],Hanzi_2424_HWZS_Shang[],Hanzi_2424_HWZS_Zhi[],Hanzi_2424_HWZS_Ke[];
extern uchar code Hanzi_2424_HWZS_Ji1[],Hanzi_2424_HWZS_Null[],Hanzi_2424_HWZS_Guan[],Hanzi_2424_HWZS_Men[],Hanzi_2424_HWZS_Yan[],Hanzi_2424_HWZS_Shi[];
extern uchar code Hanzi_2424_HWZS_Hei[],Hanzi_2424_HWZS_Ma[],Hanzi_2424_HWZS_Seng[],Hanzi_2424_HWZS_Tian[];
extern uchar code Hanzi_1616_XST_Xue[], Hanzi_1616_XST_Xi[],Hanzi_1616_XST_Zi[],Hanzi_1616_XST_Dong[],Hanzi_1616_XST_Kai[],Hanzi_1616_XST_Guan[],Hanzi_1616_XST_Dian1[];
extern uchar code Hanzi_1616_XST_Ting[],Hanzi_1616_XST_Zhi[],Hanzi_1616_XST_Men[];
extern uchar code Hanzi_1616_XST_Qing[],Hanzi_1616_XST_Shu1[],Hanzi_1616_XST_Ru[],Hanzi_1616_XST_Yong[],Hanzi_1616_XST_Hu[],Hanzi_1616_XST_Mi[];
extern uchar code char_star[];

/////////////////////////////////////////////////

#endif