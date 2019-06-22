#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#define uchar unsigned char
#define uint unsigned int

#define Contd_keyUpDown_Time 10

typedef struct{
	uchar SysMode;
	uchar ManuLevel;
	uchar SysProcess;
	uchar SysLineProcess;
	uchar ItemCursor;
	uchar ParaCursor;
}SystemStatusType;

typedef struct{
	uchar	KEY1_Status; 	
	uchar	KEY2_Status;
	uchar	KEY_Up_Status;
	uchar	KEY_Stop_Status;
	uchar	KEY_Down_Status;
}KeyStatusType;

typedef struct{
	uchar key_press;
	uchar keyin_confirm;
	uchar key_release;
}KeyInStatusType;

extern KeyStatusType KeyInPrev, KeyInCurr;
extern uchar DataBufH, DataBufL, CCMD, A_GNT, RD_FinishFlag; 
extern uchar system_run_enable;

extern void DummySingleFrameTestDataGenerate(uchar addrL, uchar addrH, uchar opDataL, uchar opDataH);
extern void AppFunRun();
//extern void AppFunRun(networkDataBuf_type* appDataBuf);
extern void SysStatusInit(SystemStatusType SysS1);

void System_Study(void);
void System_Running(void);
void User_Setting(void);
void Vendor_Setting(void);
void KeyStatusInit(void);
void KeyIn_Check(void);
void Key1_response(void);
void Key2_response(void);
void Key3_response(void);
void Key4_response(void);
void Key5_response(void);

void DisplayOperationStatus(uchar x);
extern void GetDataFromMaster(uchar DaddrH, uchar DaddrL);
extern void ClrRdParameters(void);






#endif