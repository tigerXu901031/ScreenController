#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#define uchar unsigned char
#define uint unsigned int






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
}KeyInStatusType;

extern void DummySingleFrameTestDataGenerate(uchar addrL, uchar addrH, uchar opDataL, uchar opDataH);
extern void AppFunRun(void);
extern void SysStatusInit(SystemStatusType SysS1);

void System_Study(void);
void System_Running(void);
void User_Setting(void);
void Vendor_Setting(void);












#endif