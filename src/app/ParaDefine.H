#ifndef __PARADEFINE_H__
#define __PARADEFINE_H__

/*Head file for Parameters Definition*/

#define uchar unsigned char
#define uint unsigned int

/***********MonitorParameters Definition************/
//			Const Address Name					Register Address
#define	MonitorPara_CurrentFBK_AddrH					0x30
#define	MonitorPara_CurrentFBK_AddrL					0x00

#define	MonitorPara_FreqSET_AddrH						0x30
#define	MonitorPara_FreqSET_AddrL						0x01

#define	MonitorPara_OutputPWR_AddrH						0x30
#define	MonitorPara_OutputPWR_AddrL						0x02

#define	MonitorPara_BUSVoltage_AddrH					0x30
#define	MonitorPara_BUSVoltage_AddrL					0x03

#define	MonitorPara_TorqueFBK_AddrH						0x30
#define	MonitorPara_TorqueFBK_AddrL						0x04

#define	MonitorPara_FreqFBK_AddrH						0x30
#define	MonitorPara_FreqFBK_AddrL						0x05

#define	MonitorPara_RunTimeH_AddrH						0x30
#define	MonitorPara_RunTimeH_AddrL						0x06

#define	MonitorPara_RunTimeL_AddrH						0x30
#define	MonitorPara_RunTimeL_AddrL						0x07

#define	MonitorPara_OutputVoltage_AddrH				0x30
#define	MonitorPara_OutputVoltage_AddrL				0x08

#define	MonitorPara_Position_AddrH						0x30
#define	MonitorPara_Position_AddrL						0x09

//#define	MonitorPara_PowerONTime_AddrH				0x30
//#define	MonitorPara_PowerONTime_AddrL				0x03

#define	MonitorPara_Fault_AddrH							0x30
#define	MonitorPara_Fault_AddrL							0x0A

#define	MonitorPara_IOStatusIn_AddrH					0x30
#define	MonitorPara_IOStatusIn_AddrL					0x0B

#define	MonitorPara_IOStatusOut_AddrH					0x30
#define	MonitorPara_IOStatusOut_AddrL					0x0C

#define	MonitorPara_SysStatus_AddrH						0x30
#define	MonitorPara_SysStatus_AddrL						0x0D

#define	MonitorPara_ModuleTemp_AddrH					0x30
#define	MonitorPara_ModuleTemp_AddrL					0x0E
                                          		
#define	MonitorPara_OutsideTemp_AddrH					0x30
#define	MonitorPara_OutsideTemp_AddrL					0x0F
                                          		
#define	MonitorPara_RSV3_AddrH							0x30
#define	MonitorPara_RSV3_AddrL							0x10
                                          	
#define	MonitorPara_RSV4_AddrH							0x30
#define	MonitorPara_RSV4_AddrL							0x11
                                          	
#define	MonitorPara_RSV5_AddrH							0x30
#define	MonitorPara_RSV5_AddrL							0x12
                                          	
#define	MonitorPara_ARM_Ver_AddrH						0xF0
#define	MonitorPara_ARM_Ver_AddrL						0x01
                                          		
#define	MonitorPara_FltClrStatus_AddrH					0xF0
#define	MonitorPara_FltClrStatus_AddrL					0x02

#define	MonitorPara_RSV6_AddrH								0xF0
#define	MonitorPara_RSV6_AddrL								0x03

#define	MonitorPara_TotalPOTime_AddrH					0xF0
#define	MonitorPara_TotalPOTime_AddrL					0x04

#define	MonitorPara_FltClrStatus_Invalid			0
#define	MonitorPara_FltClrStatus_Cleared			1

/***********Digital Input Definition************/
#define	GPIO_DI_X1_FunctionSel_AddrH					0x01
#define	GPIO_DI_X1_FunctionSel_AddrL					0x00

#define	GPIO_DI_X1_StatusSel_AddrH						0x01
#define	GPIO_DI_X1_StatusSel_AddrL						0x01

#define	GPIO_DI_X2_FunctionSel_AddrH					0x01
#define	GPIO_DI_X2_FunctionSel_AddrL					0x02

#define	GPIO_DI_X2_StatusSel_AddrH						0x01
#define	GPIO_DI_X2_StatusSel_AddrL						0x03

#define	GPIO_DI_X3_FunctionSel_AddrH					0x01
#define	GPIO_DI_X3_FunctionSel_AddrL					0x04

#define	GPIO_DI_X3_StatusSel_AddrH						0x01
#define	GPIO_DI_X3_StatusSel_AddrL						0x05

#define	GPIO_DI_X4_FunctionSel_AddrH					0x01
#define	GPIO_DI_X4_FunctionSel_AddrL					0x06

#define	GPIO_DI_X4_StatusSel_AddrH						0x01
#define	GPIO_DI_X4_StatusSel_AddrL						0x07

#define	GPIO_DI_X5_FunctionSel_AddrH					0x01
#define	GPIO_DI_X5_FunctionSel_AddrL					0x08

#define	GPIO_DI_X5_StatusSel_AddrH						0x01
#define	GPIO_DI_X5_StatusSel_AddrL						0x09

#define	GPIO_DI_X6_FunctionSel_AddrH					0x01
#define	GPIO_DI_X6_FunctionSel_AddrL					0x0A

#define	GPIO_DI_X6_StatusSel_AddrH						0x01
#define	GPIO_DI_X6_StatusSel_AddrL						0x0B

#define	GPIO_DI_X7_FunctionSel_AddrH					0x01
#define	GPIO_DI_X7_FunctionSel_AddrL					0x0C

#define	GPIO_DI_X7_StatusSel_AddrH						0x01
#define	GPIO_DI_X7_StatusSel_AddrL						0x0D

#define	GPIO_DI_X8_FunctionSel_AddrH					0x01
#define	GPIO_DI_X8_FunctionSel_AddrL					0x0E

#define	GPIO_DI_X8_StatusSel_AddrH						0x01
#define	GPIO_DI_X8_StatusSel_AddrL						0x0F

#define	GPIO_DI_X9_FunctionSel_AddrH					0x01
#define	GPIO_DI_X9_FunctionSel_AddrL					0x10

#define	GPIO_DI_X9_StatusSel_AddrH						0x01
#define	GPIO_DI_X9_StatusSel_AddrL						0x11

#define	GPIO_DI_X10_FunctionSel_AddrH					0x01
#define	GPIO_DI_X10_FunctionSel_AddrL					0x12

#define	GPIO_DI_X10_StatusSel_AddrH						0x01
#define	GPIO_DI_X10_StatusSel_AddrL						0x13

#define	GPIO_DI_X11_FunctionSel_AddrH					0x01
#define	GPIO_DI_X11_FunctionSel_AddrL					0x14

#define	GPIO_DI_X11_StatusSel_AddrH						0x01
#define	GPIO_DI_X11_StatusSel_AddrL						0x15

#define	GPIO_DI_X12_FunctionSel_AddrH					0x01
#define	GPIO_DI_X12_FunctionSel_AddrL					0x16

#define	GPIO_DI_X12_StatusSel_AddrH						0x01
#define	GPIO_DI_X12_StatusSel_AddrL						0x17

/***********Digital Input Selections************/
#define	GPIO_DI_FuncSel_None									0x00
#define	GPIO_DI_FuncSel_AB										0x01
#define	GPIO_DI_FuncSel_DL_POS								0x02
#define	GPIO_DI_FuncSel_MaxDL_POS							0x03
#define	GPIO_DI_FuncSel_UL_POS								0x04
#define	GPIO_DI_FuncSel_MaxUL_POS							0x05
#define	GPIO_DI_FuncSel_PreL_SW								0x06
#define	GPIO_DI_FuncSel_INC_A									0x07
#define	GPIO_DI_FuncSel_INC_B									0x08
#define	GPIO_DI_FuncSel_Rader_EM							0x09
#define	GPIO_DI_FuncSel_OpticalSW							0x0A
#define	GPIO_DI_FuncSel_OpenDoor							0x0B
#define	GPIO_DI_FuncSel_CloseDoor							0x0C
#define	GPIO_DI_FuncSel_Stop									0x0D
#define	GPIO_DI_FuncSel_Emergency							0x0E
#define	GPIO_DI_FuncSel_RSV										0x0F
#define	GPIO_DI_FuncSel_Service								0x10
#define	GPIO_DI_FuncSel_Auto_Close						0x11
#define	GPIO_DI_FuncSel_AutoCycleTest_EN			0x12
#define	GPIO_DI_FuncSel_SDoorOpen							0x18
#define	GPIO_DI_FuncSel_ML										0x19
#define	GPIO_DI_FuncSel_InterLockStatusIN			0x1A
#define	GPIO_DI_FuncSel_InterLockOpenIN				0x1B
#define	GPIO_DI_FuncSel_LineSW								0x1C

#define	GPIO_DI_StatusSel_NO									0
#define	GPIO_DI_StatusSel_NC									1

/***********Digital Outputs ************/

#define	GPIO_DO_Relay1_AddrH									0x01
#define	GPIO_DO_Relay1_AddrL									0x1E

#define	GPIO_DO_Relay2_AddrH									0x01
#define	GPIO_DO_Relay2_AddrL									0x1F

#define	GPIO_DO_Relay3_AddrH									0x01
#define	GPIO_DO_Relay3_AddrL									0x20

#define	GPIO_DO_Relay4_AddrH									0x01
#define	GPIO_DO_Relay4_AddrL									0x21

#define	GPIO_DO_Relay5_AddrH									0x01
#define	GPIO_DO_Relay5_AddrL									0x22

#define	GPIO_DO_Relay6_AddrH									0x01
#define	GPIO_DO_Relay6_AddrL									0x23

#define	GPIO_DO_Relay7_AddrH									0x01
#define	GPIO_DO_Relay7_AddrL									0x24

#define	GPIO_DO_Relay8_AddrH									0x01
#define	GPIO_DO_Relay8_AddrL									0x25

#define	GPIO_DO_Relay9_AddrH									0x01
#define	GPIO_DO_Relay9_AddrL									0x26

/***********Digital Outputs Selections************/
#define	GPIO_DO_RLY_Sel_None									0x00
#define	GPIO_DO_RLY_Sel_Uplimit								0x01
#define	GPIO_DO_RLY_Sel_DoorOpenOutput				0x02
#define	GPIO_DO_RLY_Sel_DoorCloseOutput				0x03
#define	GPIO_DO_RLY_Sel_Rsv1									0x04
#define	GPIO_DO_RLY_Sel_Rsv2									0x05
#define	GPIO_DO_RLY_Sel_Downlimit							0x06
#define	GPIO_DO_RLY_Sel_TrafficLight1					0x07
#define	GPIO_DO_RLY_Sel_TrafficLight2					0x08
#define	GPIO_DO_RLY_Sel_ServiceLight					0x09
#define	GPIO_DO_RLY_Sel_RunningOutput					0x0A
#define	GPIO_DO_RLY_Sel_Rsv3									0x0B
#define	GPIO_DO_RLY_Sel_Rsv4									0x0C
#define	GPIO_DO_RLY_Sel_Rsv5									0x0D
#define	GPIO_DO_RLY_Sel_Rsv6									0x0E
#define	GPIO_DO_RLY_Sel_Rsv7									0x0F
#define	GPIO_DO_RLY_Sel_InterLockOut					0x10
#define	GPIO_DO_RLY_Sel_InterLockOut1					0x11
#define	GPIO_DO_RLY_Sel_FaultOut							0x12

/*********** Function Parameters ************/
#define	FuncPara_PARA_Prog_AddrH							0x02
#define	FuncPara_PARA_Prog_AddrL							0x00

#define	FuncPara_POSLMT_Type_AddrH						0x02
#define	FuncPara_POSLMT_Type_AddrL						0x01

#define	FuncPara_LMT_STUDY_AddrH							0x02
#define	FuncPara_LMT_STUDY_AddrL							0x02

#define	FuncPara_Motor_DIRT_AddrH							0x02
#define	FuncPara_Motor_DIRT_AddrL							0x03

#define	FuncPara_Encoder_DIRT_AddrH						0x02
#define	FuncPara_Encoder_DIRT_AddrL						0x04

#define	FuncPara_DoorClose_SPD1_AddrH					0x02
#define	FuncPara_DoorClose_SPD1_AddrL					0x05

#define	FuncPara_DoorOpen_SPD1_AddrH					0x02
#define	FuncPara_DoorOpen_SPD1_AddrL					0x06

#define	FuncPara_DoorClose_SPD2_AddrH					0x02
#define	FuncPara_DoorClose_SPD2_AddrL					0x07

#define	FuncPara_DoorOpen_SPD2_AddrH					0x02
#define	FuncPara_DoorOpen_SPD2_AddrL					0x08

#define	FuncPara_Debug_Speed_AddrH						0x02
#define	FuncPara_Debug_Speed_AddrL						0x09

#define	FuncPara_Fault_Speed_AddrH						0x02
#define	FuncPara_Fault_Speed_AddrL						0x0A

#define	FuncPara_INC_ENC_RES_AddrH						0x02
#define	FuncPara_INC_ENC_RES_AddrL						0x0B

#define	FuncPara_ABS_ENC_RES_AddrH						0x02
#define	FuncPara_ABS_ENC_RES_AddrL						0x0C

#define	FuncPara_ABS_ENC_REV_AddrH						0x02
#define	FuncPara_ABS_ENC_REV_AddrL						0x0D

#define	FuncPara_POSLOS_ERR_AddrH							0x02
#define	FuncPara_POSLOS_ERR_AddrL							0x0E

#define	FuncPara_POSLOS_TMT_AddrH							0x02
#define	FuncPara_POSLOS_TMT_AddrL							0x0F

#define	FuncPara_IO_MDFY_EN_AddrH							0x02
#define	FuncPara_IO_MDFY_EN_AddrL							0x10

#define	FuncPara_AutoCloseDoor_EN_AddrH				0x02
#define	FuncPara_AutoCloseDoor_EN_AddrL				0x11

#define	FuncPara_AutoCloseDoor_DelayT_AddrH		0x02
#define	FuncPara_AutoCloseDoor_DelayT_AddrL		0x12

#define	FuncPara_UpLimit_Val_AddrH						0x02
#define	FuncPara_UpLimit_Val_AddrL						0x13

#define	FuncPara_UpLimit_BUF_AddrH						0x02
#define	FuncPara_UpLimit_BUF_AddrL						0x14

#define	FuncPara_MidLimit_Val_AddrH						0x02
#define	FuncPara_MidLimit_Val_AddrL						0x15

#define	FuncPara_MidLimit_BUF_AddrH						0x02
#define	FuncPara_MidLimit_BUF_AddrL						0x16

#define	FuncPara_DownLimit_Val_AddrH					0x02
#define	FuncPara_DownLimit_Val_AddrL					0x17

#define	FuncPara_DownLimit_BUF_AddrH					0x02
#define	FuncPara_DownLimit_BUF_AddrL					0x18

#define	FuncPara_AutoTest_AddrH								0x02
#define	FuncPara_AutoTest_AddrL								0x19

#define	FuncPara_AT_DoorCloseDelay_AddrH			0x02
#define	FuncPara_AT_DoorCloseDelay_AddrL			0x1A

#define	FuncPara_AT_DoorOpenDelay_AddrH				0x02
#define	FuncPara_AT_DoorOpenDelay_AddrL				0x1B

#define	FuncPara_ResetAll_AddrH								0x02
#define	FuncPara_ResetAll_AddrL								0x1C

#define	FuncPara_AB_Mode_AddrH								0x02
#define	FuncPara_AB_Mode_AddrL								0x1D

#define	FuncPara_PON_WaitRunTime_AddrH				0x02
#define	FuncPara_PON_WaitRunTime_AddrL				0x1E

#define	FuncPara_TL1_AddrH										0x02
#define	FuncPara_TL1_AddrL										0x1F

#define	FuncPara_TL2_AddrH										0x02
#define	FuncPara_TL2_AddrL										0x20

#define	FuncPara_TP_Mode1_AddrH								0x02
#define	FuncPara_TP_Mode1_AddrL								0x21

#define	FuncPara_TP_Mode2_AddrH								0x02
#define	FuncPara_TP_Mode2_AddrL								0x22

#define	FuncPara_AbsEnc_AngOff_AddrH					0x02
#define	FuncPara_AbsEnc_AngOff_AddrL					0x23

#define	FuncPara_OptPOS_Change_AddrH					0x02
#define	FuncPara_OptPOS_Change_AddrL					0x24

#define	FuncPara_UL_HYS_AddrH									0x02
#define	FuncPara_UL_HYS_AddrL									0x25

#define	FuncPara_DL_HYS_AddrH									0x02
#define	FuncPara_DL_HYS_AddrL									0x26

#define	FuncPara_LMTPOS_StudyT_AddrH					0x02
#define	FuncPara_LMTPOS_StudyT_AddrL					0x27

#define	FuncPara_POS_Study_OverShoot_AddrH		0x02
#define	FuncPara_POS_Study_OverShoot_AddrL		0x28

#define	FuncPara_USER_CODE_AddrH							0x02
#define	FuncPara_USER_CODE_AddrL							0x29

#define	FuncPara_INT_Lock_EN_AddrH						0x02
#define	FuncPara_INT_Lock_EN_AddrL						0x2A

#define	FuncPara_ORG_SW_AddrH									0x02
#define	FuncPara_ORG_SW_AddrL									0x2B

#define	FuncPara_EncDirtStd_EN_AddrH					0x02
#define	FuncPara_EncDirtStd_EN_AddrL					0x2C

#define	POSLmtType_MEC												0x00
#define	POSLmtType_INC												0x01
#define	POSLmtType_ABS												0x02
#define	LMT_Invalid														0x00
#define	LMT_Reset															0x01
#define	Motor_Dirt_FWD												0x00
#define	Motor_Dirt_RVS												0x01
#define	Encoder_Dirt_FWD											0x00
#define	Encoder_Dirt_RVS											0x01
#define	AutoCloseDoor_DEN											0x00
#define	AutoCloseDoor_EN											0x01
#define	AutoTest_DEN													0x00
#define	AutoTest_EN1													0x01
#define	AutoTest_EN2													0x02
#define	ResetAll_DEN													0x00
#define	ResetP0_P4_EN													0x01
#define	ResetAll_EN														0x02
#define	ResetP0_P4_EN													0x01
#define	ResetAll_EN														0x02
#define	AB_Trig_Stop													0x00
#define	AB_Trig_Open													0x01
#define	TP_Mode1_Auto													0x00
#define	TP_Mode1_AOSC													0x01
#define	TP_Mode1_SOAC													0x02
#define	TP_Mode1_SOSC													0x03
#define	TP_Mode2_TPValid											0x00
#define	TP_Mode2_TPValid_SD										0x01
#define	TP_Mode2_TPValid_D										0x02
#define	INT_Lock_DEN													0x00
#define	INT_Lock_EN														0x01
#define	ORG_SW_Null														0x00
#define	ORG_SW_EN															0x01
#define	EndDirtStd_DEN												0x00
#define	EndDirtStd_EN													0x01

/*********** Communication Parameters ************/
#define	CommPara_OverTime_AddrH								0x03
#define	CommPara_OverTime_AddrL								0x00

#define	CommPara_EncSel_AddrH									0x03
#define	CommPara_EncSel_AddrL									0x01

#define	CommPara_NodeNum_AddrH								0x03
#define	CommPara_NodeNum_AddrL								0x02

#define	CommPara_RSV1_AddrH										0x03
#define	CommPara_RSV1_AddrL										0x03

#define	CommPara_RSV2_AddrH										0x03
#define	CommPara_RSV2_AddrL										0x04

#define	CommPara_RSV3_AddrH										0x03
#define	CommPara_RSV3_AddrL										0x05

#define	CommPara_RSV4_AddrH										0x03
#define	CommPara_RSV4_AddrL										0x06

#define	CommPara_RSV5_AddrH										0x03
#define	CommPara_RSV5_AddrL										0x07

#define	Encoder_Sel_KSD												0x00
#define	Encoder_Sel_TOFI1											0x01
#define	Encoder_Sel_TOFI2											0x02
#define	Encoder_Sel_TOFI3											0x03
#define	Encoder_Sel_ALWAYI										0x04

/*********** Vendor Parameters ************/
#define	VendPara_PSW_AddrH										0x04
#define	VendPara_PSW_AddrL										0x00

#define	VendPara_Mtain_LMT_AddrH							0x04
#define	VendPara_Mtain_LMT_AddrL							0x01

#define	VendPara_PWR_On_Time_LMT_AddrH				0x04
#define	VendPara_PWR_On_Time_LMT_AddrL				0x02

#define	VendPara_MFG_Date_AddrH								0x04
#define	VendPara_MFG_Date_AddrL								0x03

#define	VendPara_Rtime_LowLMT_AddrH						0x04
#define	VendPara_Rtime_LowLMT_AddrL						0x04

#define	VendPara_Rtime_HighLMT_AddrH					0x04
#define	VendPara_Rtime_HighLMT_AddrL					0x05

#define	VendPara_RSV1_AddrH										0x04
#define	VendPara_RSV1_AddrL										0x06

#define	VendPara_CLR_Rtime_AddrH							0x04
#define	VendPara_CLR_Rtime_AddrL							0x07

#define	VendPara_CLR_POT_AddrH								0x04
#define	VendPara_CLR_POT_AddrL								0x08

#define	VendPara_CLR_HISFLT_AddrH							0x04
#define	VendPara_CLR_HISFLT_AddrL							0x09

#define	VendPara_Product_SN_AddrH							0x04
#define	VendPara_Product_SN_AddrL							0x0A
                                        			
#define	Maintainance_LMT_DEN									0x00
#define	Maintainance_LMT_EN										0x01
#define	CLR_HISFLT_DEN												0x00
#define	CLR_HISFLT_EN													0x01

#define	MotionControl_AddrH										0x20
#define	MotionControl_AddrL										0x00

#define	MotionControl_Stop										0x01
#define	MotionControl_Open										0x02
#define	MotionControl_Close										0x03
		
#define	LearnModeOperation_AddrH							0x20
#define	LearnModeOperation_AddrL							0x01

#define	LMO_Null															0x00
#define	LMO_Single_Up													0x01
#define	LMO_Single_Stop												0x02
#define	LMO_Single_Down												0x03
#define	LMO_UpLMT_Confirmed										0x04
#define	LMO_DownLMT_Confirmed									0x05
#define	LMO_POS_Learning_Finished							0x06

#define	System_Status_Init	0x00
#define	System_Status_Learn	0x01
#define	System_Status_Run	0x02
#define	System_Status_SingleMv	0x03
#define	System_Status_Repair	0x04


typedef struct{
	uchar i;
	
}Monitor_Parameters;



/////////////////////////////////////////////////

#endif