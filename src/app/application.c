/*****************application.c*************************/

#include "../drv/STC8.H"
#include "../app/ParaDefine.H"
#include "../app/HMI.H" 
#include "../app/application.H"

#include "intrins.h"
#include "../drv/19296p1.H"
#include "../drv/uartDrv.h"
#include "../main/task.h"


sbit KEY1 		= P1^0;
sbit KEY2 		= P0^7;
sbit KEY_Up 	= P0^6;
sbit KEY_Stop = P0^5;
sbit KEY_Down = P0^4;

networkDataBuf_type testNwData1;
networkDataBuf_type testSetNwData1;
KeyInStatusType KeyInPrev, KeyInCurr;


void SysStatusInit(SystemStatusType SysS1)
{
	SysS1.SysMode  				=	0;
	SysS1.ManuLevel				=	0;
	SysS1.SysProcess			=	0;
	SysS1.SysLineProcess	=	0;
	SysS1.ItemCursor			=	0;
	SysS1.ParaCursor			=	0;
}

void DummySingleFrameTestDataGenerate(uchar addrL, uchar addrH, uchar opDataL, uchar opDataH)
{
    testSetNwData1.dataLength =1;
    testSetNwData1.networkData[0].cmd = 0x03;
    testSetNwData1.networkData[0].add[0] = addrL;
    testSetNwData1.networkData[0].add[1] = addrH;
    testSetNwData1.networkData[0].opData[0] = opDataL;
    testSetNwData1.networkData[0].opData[1] = opDataH;   
}

void AppFunRun(void)
{
	
	//getNetworkData(&testNwData);
	//setNetworkData(&testSetNwData);
	switch (SysStatus.SysMode)
	{
		case 0:				//Study Mode
			System_Study();
			break;
		case 1:				//Running Mode
			System_Running();
			break;
		case 2:				//User Set Mode
			User_Setting();
			break;
		case 3:				//Vendor Set Mode
			Vendor_Setting();
			break;
	}	
}