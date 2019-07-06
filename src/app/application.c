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
sbit KEY_Up 	= P0^4;
sbit KEY_Stop = P0^5; 
sbit KEY_Down = P0^6;

networkDataBuf_type testNwData1;
networkDataBuf_type testSetNwData1;
KeyStatusType KeyInPrev, KeyInCurr;
KeyInStatusType K1, K2, K3, K4, K5;
uchar POS_StudyFinished = 0;
uchar Page_New = 1;
uchar T10ms_Count, T100ms_Count=0, T1s_Count=0;
uint KeyinTime1,KeyinTime2,KeyinTime3,KeyinTime4,KeyinTime5;
uchar SetGetInterval=0;
//uchar DataAddrH, DataAddrL;
uchar DataBufH, DataBufL, CCMD, A_GNT, RD_FinishFlag=0;
uchar SysStatusReady = 0;
uchar RD_BSY=0;

	unsigned char dummyCnt;
    unsigned char dummyWriteCmd = 0x06, dummyReadCmd = 0x03;
    unsigned char dummyWriteDataL = 0x02, dummyReadDataL = 0x01;
    unsigned char dummyWriteDataH = 0x00, dummyReadDataH = 0x00;


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
							Display_RunTimeL();
							Display_RunTimeH();
						}
			break;
	//	case 4:
	//		SysStatus.SysMode = 1;
	//		Page_New = 1;
	//		POS_StudyFinished = 1;
	//			if(Page_New)
	//			{
	//				SysStatus.ManuLevel = 4;			//Running Page
	//				Disp_Page_RunningMode();
	//				Page_New = 0;
	//			}
	//				else
	//					{
	//						Display_Encoder_Number(1);		//encoder value update
	//						Display_I_current();
	//						Display_F_frequency();
	//						Display_RunTime();
	//					}
			break;
		default: 
			SysStatus.ManuLevel = 0; 
			break;
	}
}

void System_Running(void)
{
	if(Page_New)
				{
					SysStatus.ManuLevel = 4;			//system running manu
					Disp_Page_RunningMode();
					Page_New = 0;
					RD_BSY = 0;
				}
					else
						{
							Display_Encoder_Number(1);		//encoder value update
							Display_I_current();
							Display_F_frequency();
							Display_RunTimeL();
							Display_RunTimeH(); 
							Display_ATMT();
						}
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
								if(SysStatus.ManuLevel==2)
									{
										T100ms_Count++;
										if(T100ms_Count==Contd_keyUpDown_Time)	//100ms time
											{
												//setNetworkData(LearnModeOperation_AddrL, LearnModeOperation_AddrH, LMO_Single_Up, 0x00, 0x06);
													DataBufH = 0;
													DataBufL = LMO_Single_Up;
													CCMD = 0x06;
													A_GNT = 0x00;
													setNetworkData(LearnModeOperation_AddrL, LearnModeOperation_AddrH, &DataBufL, &DataBufH, &CCMD, &A_GNT);
												T100ms_Count = 0;
											}	
											else
												{;}		
									}
									else
										{;}
													
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
								if((SysStatus.ManuLevel==2)||(SysStatus.ManuLevel==3))
									{
										T100ms_Count++;
										if(T100ms_Count==Contd_keyUpDown_Time)	//100ms time
											{
													DataBufH = 0;
													DataBufL = LMO_Single_Stop;
													CCMD = 0x06;
													A_GNT = 0x00;
													setNetworkData(LearnModeOperation_AddrL, LearnModeOperation_AddrH, &DataBufL, &DataBufH, &CCMD, &A_GNT);

												T100ms_Count = 0;
											}	
											else
												{;}		
									}
									else
										{;}
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
								if(SysStatus.ManuLevel==3)
									{
										T100ms_Count++;
										if(T100ms_Count==Contd_keyUpDown_Time)	//100ms time
											{
													DataBufH = 0;
													DataBufL = LMO_Single_Down;
													CCMD = 0x06;
													A_GNT = 0x00;
													setNetworkData(LearnModeOperation_AddrL, LearnModeOperation_AddrH, &DataBufL, &DataBufH, &CCMD, &A_GNT);
												T100ms_Count = 0;
											}	
											else
												{;}		
									}
									else
										{;}								
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
					SysStatus.ManuLevel -=1;
					Page_New = 1;
					break;
				case 2:		//up limit confirm page
					SysStatus.ManuLevel -=1;
					Page_New = 1;
					break;
				case 3:		//close door delay time confirm page
					SysStatus.ManuLevel -=1;
					Page_New = 1;
					break;
				case 4:		//system running page
					SysStatus.ManuLevel -=1;
					Page_New = 1;
					break;
				default: break;
			}
		}
if(SysStatus.SysMode ==1)		//Running Mode
	{
		
		setNetworkData(FuncPara_LMT_STUDY_AddrL, FuncPara_LMT_STUDY_AddrH, &DataBufL, &DataBufH, &CCMD, &A_GNT);
		SysStatus.SysMode = 0;		//change back to Study Mode
		POS_StudyFinished = 0;		//unstudied
		SysStatus.ManuLevel = 0;
		Page_New = 1;
	}
if(SysStatus.SysMode ==2)		//User Set Mode
	{
		SysStatus.SysMode = 1;		//change back to Study Mode
		POS_StudyFinished = 1;		//unstudied
		SysStatus.ManuLevel = 4;
		Page_New = 1;
	}
if(SysStatus.SysMode ==3)		//Vendor Set Mode
	{
		SysStatus.SysMode = 2;		//change back to Study Mode
		POS_StudyFinished = 1;		//unstudied
		SysStatus.ManuLevel = 5;
		Page_New = 1;
	}
}

void Key2_response(void)
{
	if(SysStatus.SysMode ==0)		//Study Mode
		{
			SysStatus.ManuLevel++;
			Page_New = 1;
			if(SysStatus.ManuLevel==4)
				{
					SysStatus.SysMode = 1;
					POS_StudyFinished = 1;
					Page_New = 1;
					SysStatus.ManuLevel = 3;
				}
				else
					{;}
		}
	if(SysStatus.SysMode ==1)		//Running Mode
		{
			//Enter into User Set Mode
			//not open further mode in first stage
//			SysStatus.ManuLevel++;
			//Page_New = 1;
//			if(SysStatus.ManuLevel==5)
//				{
//					SysStatus.SysMode = 2;
//					Page_New = 1;
//					SysStatus.ManuLevel = 4;
//				}
//				else
//					{;}
		}
	if(SysStatus.SysMode ==2)		//User Set Mode
		{
			//Enter into Vendor Set Mode
			SysStatus.ManuLevel++;
			//Page_New = 1;
			if(SysStatus.ManuLevel==6)
				{
					SysStatus.SysMode = 3;
					Page_New = 1;
					SysStatus.ManuLevel = 5;
				}
				else
					{;}			
		}
	if(SysStatus.SysMode ==3)		//Vendor Set Mode
		{
			SysStatus.ManuLevel++;
			//Page_New = 1;
			if(SysStatus.ManuLevel==7)
				{
					SysStatus.SysMode = 4;
					Page_New = 1;
					SysStatus.ManuLevel = 6;
				}
				else
					{;}			
		}
		else
			{;}
}

void Key3_response(void)
{
	switch(SysStatus.ManuLevel)
	{
		case 0:		//Motor direction confirm page, no action
		break;
		
		case 1:		//down limit study page, send "MoveUp" signal to mainmachine (seems rarely happened)
		//setNetworkData(FuncPara_Motor_DIRT_AddrL, FuncPara_Motor_DIRT_AddrH, Motor_Dirt_RVS, 0x00, 0x06);
		break;
		
		case 2:		//Up limit study page, send "MoveUp" signal to mainmachine
		//setNetworkData(FuncPara_Motor_DIRT_AddrL, FuncPara_Motor_DIRT_AddrH, Motor_Dirt_RVS, 0x00, 0x06);
		break;
		
		case 3:		//close door delay time set page, set delaytime numbers, no action
		break;
		
		case 4:		//system running page, one push send one control command
		dummyWriteDataL = 0x02;
		dummyWriteDataH = 0x00;
		dummyWriteCmd = 0x06;
		dummyCnt = 0x00;
		setNetworkData(0x00, 0x20, &dummyWriteDataL, &dummyWriteDataH, &dummyWriteCmd, &dummyCnt);
		DisplayOperationStatus(MotionControl_Open);
		break;
		default:break;	
	}
	
//	if(SysStatus.SysMode ==0)		//Study Mode
//		{
//			if(SysStatus.ManuLevel == 0)
//			{
//				
//			}
//			else
//			{
//				
//			}
//		}
//	if(SysStatus.SysMode ==1)		//Running Mode
//		{
//			
//		}
//	if(SysStatus.SysMode ==2)		//User Set Mode
//		{
//			
//		}
//	if(SysStatus.SysMode ==3)		//Vendor Set Mode
//		{
//			
//		}	
}

void Key4_response(void)
{
	switch(SysStatus.ManuLevel)
	{
		case 0:		//Motor direction confirm page, no action
		break;
		
		case 1:		//down limit study page, send "Stop" signal to mainmachine (seems rarely happened)
		//setNetworkData(FuncPara_Motor_DIRT_AddrL, FuncPara_Motor_DIRT_AddrH, Motor_Dirt_RVS, 0x00, 0x06);
		break;
		
		case 2:		//Up limit study page, send "MoveUp" signal to mainmachine
		break;
		
		case 3:		//close door delay time set page, set delaytime numbers
		break;
		
		case 4:		//system running page, one push send one control command
			dummyWriteDataL = 0x01;
			dummyWriteDataH = 0x00;
			dummyWriteCmd = 0x06;
			dummyCnt = 0x00;
			setNetworkData(0x00, 0x20, &dummyWriteDataL, &dummyWriteDataH, &dummyWriteCmd, &dummyCnt);
			DisplayOperationStatus(MotionControl_Stop);
		break;
		
		default:break;	
	}
//	if(SysStatus.SysMode ==0)		//Study Mode
//		{
//			;
//		}
//	if(SysStatus.SysMode ==1)		//Running Mode
//		{
//			
//		}
//	if(SysStatus.SysMode ==2)		//User Set Mode
//		{
//			
//		}
//	if(SysStatus.SysMode ==3)		//Vendor Set Mode
//		{
//			
//		}	
}

void Key5_response(void)
{
	switch(SysStatus.ManuLevel)
	{
		case 0:		//Motor direction confirm page, no action
		break;
		
		case 1:		//down limit study page, send "MoveDown" signal to mainmachine 
		//setNetworkData(FuncPara_Motor_DIRT_AddrL, FuncPara_Motor_DIRT_AddrH, Motor_Dirt_RVS, 0x00, 0x06);
		break;
		
		case 2:		//Up limit study page, send "MoveDown" signal to mainmachine, (seems rarely happened)
		break;
		
		case 3:		//close door delay time set page, set delaytime numbers, two functions: spot move or longpress shift
		break;
		
		case 4:		//system running page, one push send one control command
			dummyWriteDataL = 0x03;
			dummyWriteDataH = 0x00;
			dummyWriteCmd = 0x06;
			dummyCnt = 0x00;
			setNetworkData(0x00, 0x20, &dummyWriteDataL, &dummyWriteDataH, &dummyWriteCmd, &dummyCnt);
			DisplayOperationStatus(MotionControl_Close); 
		break;
		default: break;
		}	
//	if(SysStatus.SysMode ==0)		//Study Mode
//		{
//			;
//		}
//	if(SysStatus.SysMode ==1)		//Running Mode
//		{
//			
//		}
//	if(SysStatus.SysMode ==2)		//User Set Mode
//		{
//			
//		}
//	if(SysStatus.SysMode ==3)		//Vendor Set Mode
//		{
//			
//		}	
}

void DisplayOperationStatus(uchar x)
{
	if(x==1)
		{		//MotionControl_Stop	
			Hanzi_Disp_16x16(97, 8, Hanzi_1616_XST_Ting, 0);
			Hanzi_Disp_16x16(113, 8, Hanzi_1616_XST_Zhi, 0);
		}
	if(x==2)
		{		//MotionControl_Open
			Hanzi_Disp_16x16(97, 8, Hanzi_1616_XST_Kai, 0);
			Hanzi_Disp_16x16(113, 8, Hanzi_1616_XST_Men, 0);
		}
	if(x==3)
		{		//MotionControl_Close
			Hanzi_Disp_16x16(97, 8, Hanzi_1616_XST_Guan, 0);
			Hanzi_Disp_16x16(113, 8, Hanzi_1616_XST_Men, 0);
		}
}

void SysMode_Set(uchar x)	//only for system mode setting during debugging
{
	SysStatus.SysMode = x;
}

void setCommParameters(uchar bufh, uchar bufl, uchar cmd, uchar aCnt)
{
	DataBufH = bufh;
	DataBufL = bufl;
	CCMD = cmd;
	A_GNT = aCnt;
}

void agcnt_Check(void)
{
	if(A_GNT<=10)								//data available
					{
						RD_FinishFlag = 1;
					}
					else
						{RD_FinishFlag = 0;}
//	RD_FinishFlag = 1;
}

void GetDataFromMaster(uchar DaddrH, uchar DaddrL)
{
	if(!RD_FinishFlag)
			{
					if(SetGetInterval==0)							//send read command
						{
							setCommParameters(0, 0, 3, 0);		//clr read buffer
							setNetworkData(DaddrL, DaddrH, &DataBufL, &DataBufH, &CCMD, &A_GNT);
							SetGetInterval++;
						}
						else
							{
								getNetworkData(DaddrL, DaddrH, &DataBufL, &DataBufH, &CCMD, &A_GNT);				//check data availability every cycle
								if(A_GNT<=10)								//data available
									{
										RD_FinishFlag = 1; 
									}
									else
										{RD_FinishFlag = 0;}
								SetGetInterval++;
								if(SetGetInterval>8)
									{SetGetInterval = 0;}			//allow to resend read command
									else 
										{;}
							}
				} 
				else
					{
						//RD_FinishFlag = 0;      
						SetGetInterval = 0;
					}
	//getNetworkData(uchar addL, uchar addH, uchar *Ldata, uchar *Hdata, uchar *cmd, uchar *agingCnt);
 	//setNetworkData(uchar addL, uchar addH, uchar *Ldata, uchar *Hdata, uchar *cmd, uchar *agingCnt);
}


//void AppFunRun(networkDataBuf_type* appDataBuf)
void AppFunRun()
{
	// SysStatusReady =1;
	// POS_StudyFinished = 1;
	// SysStatus.SysMode = 1;
	// SysStatus.ManuLevel = 4;
	
	if(SysStatusReady)		//system status is 0x01 or 0x02
		{
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
		else				//communication with master check not finished
			{
	//				//position learning status check during first power on
	//				if(!POS_StudyFinished)			//position learning not finished
	//					{
//				RD_FinishFlag = 0;
				//setCommParameters(0, 0, 3, 0);
				getNetworkData(MonitorPara_SysStatus_AddrL, MonitorPara_SysStatus_AddrH, &DataBufL, &DataBufH, &CCMD, &A_GNT);				//check data availability every cycle
				//agcnt_Check();
					if(A_GNT<=10)								//data available
					{
						RD_FinishFlag = 1;
					}
					else
						{RD_FinishFlag = 0;}
				if(RD_FinishFlag)								//status reading finished
				{
					if(DataBufL==System_Status_Run)
						{
							POS_StudyFinished = 1;
							SysStatus.SysMode = 1;			
						}
						else
							{
								POS_StudyFinished = 0;
								SysStatus.SysMode = 0;
								SysStatus.ManuLevel = 0;
							}
					SysStatusReady = 1;
					RD_FinishFlag = 0;	
				}
				else
					{
						SysStatusReady = 0;
						RD_FinishFlag = 0;
					}
//						}
//						else											//position learning finished
//							{SysStatusReady = 1;}
//							}
			}
}


/* void AppFunRun1(void)
{
	if(!SysStatusReady)		//system is ready
		{
			RD_FinishFlag = 0;
			GetDataFromMaster(MonitorPara_SysStatus_AddrH, MonitorPara_SysStatus_AddrL);
				if(RD_FinishFlag)								//status reading finished
				{
					if(DataBufL==System_Status_Run)
						{
							POS_StudyFinished = 1;
							SysStatus.SysMode = 1;
						}
						else
							{
								POS_StudyFinished = 0;
								SysStatus.SysMode = 0;
							}
					SysStatusReady = 1;	
				}
				else
					{SysStatusReady = 0;}
		}
			else
				{
					T1s_Count++;
					if(T1s_Count>100)
						{
							SysStatusReady = 0;
						}
						else
							{;}
				}
} */