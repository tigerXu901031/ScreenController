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
KeyStatusType KeyInPrev, KeyInCurr;
KeyInStatusType K1, K2, K3, K4, K5;
uchar POS_StudyFinished = 0;
uchar Page_New = 1;
uchar T10ms_Count, T100ms_Count, T1s_Count;
uint KeyinTime1,KeyinTime2,KeyinTime3,KeyinTime4,KeyinTime5;


void SysStatusInit(SystemStatusType SysS1)
{
	SysS1.SysMode  				=	0;
	SysS1.ManuLevel				=	0;
	SysS1.SysProcess			=	0;
	SysS1.SysLineProcess	=	0;
	SysS1.ItemCursor			=	0;
	SysS1.ParaCursor			=	0;
}

void KeyStatusInit(void)
{
	KeyInPrev.KEY1_Status = 0; 	
	KeyInPrev.KEY2_Status = 0;
	KeyInPrev.KEY_Up_Status = 0;
	KeyInPrev.KEY_Stop_Status = 0;
	KeyInPrev.KEY_Down_Status = 0;
	
	KeyInCurr.KEY1_Status = 0; 	
	KeyInCurr.KEY2_Status = 0;
	KeyInCurr.KEY_Up_Status = 0;
	KeyInCurr.KEY_Stop_Status = 0;
	KeyInCurr.KEY_Down_Status = 0;
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

void System_Study(void)
{
	switch (SysStatus.ManuLevel)
	{
		//not first time enter this page
		case 0:
				if(Page_New)
				{
					SysStatus.ManuLevel = 0;			//motor direction confirm page
					Motor_Parameter.Motor_Direction = 1;	// Motor direction correct
					Disp_Page_MotorDirtSet();
					Page_New = 0;
				}
					else
						{
							Display_Encoder_Number(2);		//encoder value update
							Motor_Direction_Update();			//motor direction Button update				
						}
			break;
		case 1:
				if(Page_New)
				{
					SysStatus.ManuLevel = 1;			//down limit confirm page
					Disp_Page_DownLMT_STD();
					Page_New = 0;
				}
					else
						{
							Display_Encoder_Number(2);		//encoder value update
							Display_I_current();
							Display_F_frequency();
						}
			break;
		case 2:
				if(Page_New)
				{
					SysStatus.ManuLevel = 2;			//up limit confirm page
					Disp_Page_UpLMT_STD();
					Page_New = 0;
				}
					else
						{
							Display_Encoder_Number(2);		//encoder value update
							Display_I_current();
							Display_F_frequency();
						}
			break;
		case 3:
				if(Page_New)
				{
					SysStatus.ManuLevel = 3;			//close door delay time confirm page
					Disp_Page_CloseDoor_DelayT();
					Page_New = 0;
				}
					else
						{
							Display_Encoder_Number(1);		//encoder value update
							Display_I_current();
							Display_F_frequency();
							Display_RunTime();
						}
			break;
		default: 
			SysStatus.ManuLevel = 0; 
			break;
	}
}

void System_Running(void)
{
	
}

void User_Setting(void)
{
	
}

void Vendor_Setting(void)
{
	
}

void KeyIn_Check()
{
	KeyInCurr.KEY1_Status = ~KEY1;
	if(KeyInPrev.KEY1_Status==0)
		{
			if(KeyInCurr.KEY1_Status==1)
				{	
					//key press
					K1.keyin_confirm = 0;
					KeyInPrev.KEY1_Status = 1;
				}
				else
					{
						//no action
						KeyInPrev.KEY1_Status = 0;		
					}
		}
			else
				{
					if(KeyInCurr.KEY1_Status==0)
						{
							//key release
							KeyInPrev.KEY1_Status = 0;
							if(K1.keyin_confirm == 1)
							{
								Key1_response();
								K1.keyin_confirm = 0;
							}
							else
								{;}		
						}
						else
							{
								//key pressed confirmed
								KeyInPrev.KEY1_Status = 1;
								K1.keyin_confirm = 1;								
							}
				}
	
	KeyInCurr.KEY2_Status = ~KEY2;
	if(KeyInPrev.KEY2_Status==0)
		{
			if(KeyInCurr.KEY2_Status==1)
				{	
					//key press
					K2.keyin_confirm = 0;
					KeyInPrev.KEY2_Status = 1;
				}
				else
					{
						//no action
						KeyInPrev.KEY2_Status = 0;		
					}
		}
			else
				{
					if(KeyInCurr.KEY2_Status==0)
						{
							//key release
							KeyInPrev.KEY2_Status = 0;
							if(K2.keyin_confirm == 1)
							{
								Key2_response();
								K2.keyin_confirm = 0;
							}
							else
								{;}		
						}
						else
							{
								//key pressed confirmed
								KeyInPrev.KEY2_Status = 1;
								K2.keyin_confirm = 1;								
							}
				}
	
	KeyInCurr.KEY_Up_Status = ~KEY_Up;
	if(KeyInPrev.KEY_Up_Status==0)
		{
			if(KeyInCurr.KEY_Up_Status==1)
				{	
					//key press
					K3.keyin_confirm = 0;
					KeyInPrev.KEY_Up_Status = 1;
				}
				else
					{
						//no action
						KeyInPrev.KEY_Up_Status = 0;		
					}
		}
			else
				{
					if(KeyInCurr.KEY_Up_Status==0)
						{
							//key release
							KeyInPrev.KEY_Up_Status = 0;
							if(K3.keyin_confirm == 1)
							{
								Key3_response();
								K3.keyin_confirm = 0;
							}
							else
								{;}		
						}
						else
							{
								//key pressed confirmed
								KeyInPrev.KEY_Up_Status = 1;
								K3.keyin_confirm = 1;								
							}
				}
	
	KeyInCurr.KEY_Stop_Status = ~KEY_Stop;
	if(KeyInPrev.KEY_Stop_Status==0)
		{
			if(KeyInCurr.KEY_Stop_Status==1)
				{	
					//key press
					K4.keyin_confirm = 0;
					KeyInPrev.KEY_Stop_Status = 1;
				}
				else
					{
						//no action
						KeyInPrev.KEY_Stop_Status = 0;		
					}
		}
			else
				{
					if(KeyInCurr.KEY_Stop_Status==0)
						{
							//key release
							KeyInPrev.KEY_Stop_Status = 0;
							if(K4.keyin_confirm == 1)
							{
								Key4_response();
								K4.keyin_confirm = 0;
							}
							else
								{;}		
						}
						else
							{
								//key pressed confirmed
								KeyInPrev.KEY_Stop_Status = 1;
								K4.keyin_confirm = 1;								
							}
				}
	
	KeyInCurr.KEY_Down_Status = ~KEY_Down;
	if(KeyInPrev.KEY_Down_Status==0)
		{
			if(KeyInCurr.KEY_Down_Status==1)
				{	
					//key press
					K5.keyin_confirm = 0;
					KeyInPrev.KEY_Down_Status = 1;
				}
				else
					{
						//no action
						KeyInPrev.KEY_Down_Status = 0;		
					}
		}
			else
				{
					if(KeyInCurr.KEY_Down_Status==0)
						{
							//key release
							KeyInPrev.KEY_Down_Status = 0;
							if(K5.keyin_confirm == 1)
							{
								Key5_response();
								K5.keyin_confirm = 0;
							}
							else
								{;}		
						}
						else
							{
								//key pressed confirmed
								KeyInPrev.KEY_Down_Status = 1;
								K5.keyin_confirm = 1;								
							}
				}
}

//void setNetworkData(unsigned char addL, unsigned char addH, unsigned char *dataL, unsigned char *dataH, unsigned char cmd)
void Key1_response(void)
{
	if(SysStatus.SysMode ==0)		//Study Mode
		{
			switch(SysStatus.ManuLevel)
			{
				case 0:		//motor direction confirm page
					if(Motor_Parameter.Motor_Direction == 1)
						{
							Motor_Parameter.Motor_Direction = 0;	//change motor direction to reverse
							//setNetworkData(FuncPara_Motor_DIRT_AddrL, FuncPara_Motor_DIRT_AddrH, Motor_Dirt_RVS, 0x00, 0x06);
						} //change motor direction
						else if(Motor_Parameter.Motor_Direction == 0)
							{
								Motor_Parameter.Motor_Direction = 1;
								//setNetworkData(FuncPara_Motor_DIRT_AddrL, FuncPara_Motor_DIRT_AddrH, Motor_Dirt_FWD, 0x00, 0x06);
							}
					break;
				case 1:		//down limit confirm page
					
					break;
				case 2:		//up limit confirm page
					
					break;
				case 3:		//close door delay time confirm page
					
					break;
				default: break;
			}
		}
	if(SysStatus.SysMode ==1)		//Running Mode
		{
			
		}
	if(SysStatus.SysMode ==2)		//User Set Mode
		{
			
		}
	if(SysStatus.SysMode ==3)		//Vendor Set Mode
		{
			
		}
}

void Key2_response(void)
{
	if(SysStatus.SysMode ==0)		//Study Mode
		{
			SysStatus.ManuLevel++;
			Page_New = 1;
			if(SysStatus.ManuLevel>3)
				{
					SysStatus.SysMode = 1;
				}
				else
					{;}
		}
	if(SysStatus.SysMode ==1)		//Running Mode
		{
			
		}
	if(SysStatus.SysMode ==2)		//User Set Mode
		{
			
		}
	if(SysStatus.SysMode ==3)		//Vendor Set Mode
		{
			
		}
}

void Key3_response(void)
{
	if(SysStatus.SysMode ==0)		//Study Mode
		{
			;
		}
	if(SysStatus.SysMode ==1)		//Running Mode
		{
			
		}
	if(SysStatus.SysMode ==2)		//User Set Mode
		{
			
		}
	if(SysStatus.SysMode ==3)		//Vendor Set Mode
		{
			
		}	
}

void Key4_response(void)
{
	if(SysStatus.SysMode ==0)		//Study Mode
		{
			;
		}
	if(SysStatus.SysMode ==1)		//Running Mode
		{
			
		}
	if(SysStatus.SysMode ==2)		//User Set Mode
		{
			
		}
	if(SysStatus.SysMode ==3)		//Vendor Set Mode
		{
			
		}	
}

void Key5_response(void)
{
	if(SysStatus.SysMode ==0)		//Study Mode
		{
			;
		}
	if(SysStatus.SysMode ==1)		//Running Mode
		{
			
		}
	if(SysStatus.SysMode ==2)		//User Set Mode
		{
			
		}
	if(SysStatus.SysMode ==3)		//Vendor Set Mode
		{
			
		}	
}

void SysMode_Set(uchar x)	//only for system mode setting during debugging
{
	SysStatus.SysMode = x;
}

//void AppFunRun(networkDataBuf_type* appDataBuf)
void AppFunRun()
{
	
	//getNetworkData(&testNwData);
	//setNetworkData(&testSetNwData);
	
	//read system mode from main machine, Addr: 0x300D
	//DummySingleFrameTestDataGenerate(MonitorPara_SysStatus_AddrL, MonitorPara_SysStatus_AddrH, uchar opDataL, uchar opDataH);
	
	if(POS_StudyFinished)
		{
				switch (SysStatus.SysMode)
				{
					case 1:				//Running Mode
						System_Running();
						break;
					case 2:				//User Set Mode
						User_Setting();
						break;
					case 3:				//Vendor Set Mode
						Vendor_Setting();
						break;
					default:break;
				}	
		}
		else
			{
				SysStatus.SysMode = 0;		//system in study mode
				System_Study();
			}
	KeyIn_Check();
	
}