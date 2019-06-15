/*
Head file for Parameters Definition
*/

#define uchar unsigned char
#define uint unsigned int

//MonitorParameters Definition
//			Const Address Name					Register Address
#define	MonitorPara_RunTimeH_Addr							0x3001
#define	MonitorPara_RunTimeL_Addr							0x3002
#define	MonitorPara_PowerONTime_Addr					0x3003
#define	MonitorPara_Position_Addr							0x3004
#define	MonitorPara_FreqFBK_Addr							0x3005
#define	MonitorPara_FreqSET_Addr							0x3006
#define	MonitorPara_BUSVoltage_Addr						0x3007
#define	MonitorPara_OutputVoltage_Addr				0x3008
#define	MonitorPara_CurrentFBK_Addr						0x3009
#define	MonitorPara_Fault_Addr								0x300A
#define	MonitorPara_IOStatusIn_Addr						0x300B
#define	MonitorPara_IOStatusOut_Addr					0x300C
#define	MonitorPara_SystemStatus_Addr					0x300D
#define	MonitorPara_Reserve1_Addr							0x300E
#define	MonitorPara_Reserve2_Addr							0x300F
#define	MonitorPara_Reserve3_Addr							0x3010
#define	MonitorPara_Reserve4_Addr							0x3011
#define	MonitorPara_Reserve5_Addr							0x3012

#define	MonitorPara_ARM_Ver_Addr							0xF001
#define	MonitorPara_FaultClearStatus_Addr			0xF002
#define	MonitorPara_Reserve6_Addr							0xF003
#define	MonitorPara_TotalPowerONTime_Addr			0xF004
#define	MonitorPara_FaultClearStatus_Invalid	0
#define	MonitorPara_FaultClearStatus_Cleared	1
		
#define	GPIO_DI_X1_FunctionSel_Addr						0x0100
#define	GPIO_DI_X1_StatusSel_Addr							0x0101
#define	GPIO_DI_X2_FunctionSel_Addr						0x0102
#define	GPIO_DI_X2_StatusSel_Addr							0x0103
#define	GPIO_DI_X3_FunctionSel_Addr						0x0104
#define	GPIO_DI_X3_StatusSel_Addr							0x0105
#define	GPIO_DI_X4_FunctionSel_Addr						0x0106
#define	GPIO_DI_X4_StatusSel_Addr							0x0107
#define	GPIO_DI_X5_FunctionSel_Addr						0x0108
#define	GPIO_DI_X5_StatusSel_Addr							0x0109
#define	GPIO_DI_X6_FunctionSel_Addr						0x010A
#define	GPIO_DI_X6_StatusSel_Addr							0x010B
#define	GPIO_DI_X7_FunctionSel_Addr						0x010C
#define	GPIO_DI_X7_StatusSel_Addr							0x010D
#define	GPIO_DI_X8_FunctionSel_Addr						0x010E
#define	GPIO_DI_X8_StatusSel_Addr							0x011F
#define	GPIO_DI_X9_FunctionSel_Addr						0x0110
#define	GPIO_DI_X9_StatusSel_Addr							0x0111
#define	GPIO_DI_X10_FunctionSel_Addr					0x0112
#define	GPIO_DI_X10_StatusSel_Addr						0x0113
#define	GPIO_DI_X11_FunctionSel_Addr					0x0114
#define	GPIO_DI_X11_StatusSel_Addr						0x0115
#define	GPIO_DI_X12_FunctionSel_Addr					0x0116
#define	GPIO_DI_X12_StatusSel_Addr						0x0117
		
#define	GPIO_DI_FunctionSel_None							0
#define	GPIO_DI_FunctionSel_Airbag						1
#define	GPIO_DI_FunctionSel_LL_Position				2
#define	GPIO_DI_FunctionSel_MaxLL_Position		3
#define	GPIO_DI_FunctionSel_UL_Position				4
#define	GPIO_DI_FunctionSel_MaxUL_Position		5
#define	GPIO_DI_FunctionSel_PreL_SW						6
#define	GPIO_DI_FunctionSel_INC_A							7
#define	GPIO_DI_FunctionSel_INC_B							8
#define	GPIO_DI_FunctionSel_Rader_EM					9
#define	GPIO_DI_FunctionSel_OpticalSW					11
#define	GPIO_DI_FunctionSel_OpenDoor					12
#define	GPIO_DI_FunctionSel_CloseDoor					13
#define	GPIO_DI_FunctionSel_Stop							14
#define	GPIO_DI_FunctionSel_Emergency					15
#define	GPIO_DI_FunctionSel_RSV								16
#define	GPIO_DI_FunctionSel_Service						17
#define	GPIO_DI_FunctionSel_Auto_Close				18
#define	GPIO_DI_FunctionSel_AutoCycleTest_EN	19
#define	GPIO_DI_FunctionSel_SDoorOpen					24
#define	GPIO_DI_FunctionSel_ML								25
#define	GPIO_DI_FunctionSel_InterLockStatusIN	26
#define	GPIO_DI_FunctionSel_InterLockOpenIN		27
#define	GPIO_DI_FunctionSel_LineSW						28
#define	GPIO_DI_StatusSel_NO									0
#define	GPIO_DI_StatusSel_NC									1
		
#define	GPIO_DO_Relay1_Addr										0x011E
#define	GPIO_DO_Relay2_Addr										0x011F
#define	GPIO_DO_Relay3_Addr										0x0120
#define	GPIO_DO_Relay4_Addr										0x0121
#define	GPIO_DO_Relay5_Addr										0x0122
#define	GPIO_DO_Relay6_Addr										0x0123
#define	GPIO_DO_Relay7_Addr										0x0124
#define	GPIO_DO_Relay8_Addr										0x0125
#define	GPIO_DO_Relay9_Addr										0x0126

#define	GPIO_DO_Relay_Sel_None								0x00
#define	GPIO_DO_Relay_Sel_Uplimit							0x01
#define	GPIO_DO_Relay_Sel_DoorOpenOutput			0x02
#define	GPIO_DO_Relay_Sel_DoorCloseOutput			0x03
#define	GPIO_DO_Relay_Sel_Rsv1								0x04
#define	GPIO_DO_Relay_Sel_Rsv2								0x05
#define	GPIO_DO_Relay_Sel_Lowlimit						0x06
#define	GPIO_DO_Relay_Sel_TrafficLight1				0x07
#define	GPIO_DO_Relay_Sel_TrafficLight2				0x08
#define	GPIO_DO_Relay_Sel_ServiceLight				0x09
#define	GPIO_DO_Relay_Sel_RunningOutput				0x0A
#define	GPIO_DO_Relay_Sel_Rsv3								0x0B
#define	GPIO_DO_Relay_Sel_Rsv4								0x0C
#define	GPIO_DO_Relay_Sel_Rsv5								0x0D
#define	GPIO_DO_Relay_Sel_Rsv6								0x0E
#define	GPIO_DO_Relay_Sel_Rsv7								0x0F
#define	GPIO_DO_Relay_Sel_InterLockOut				0x10
#define	GPIO_DO_Relay_Sel_InterLockOut1				0x11
#define	GPIO_DO_Relay_Sel_FaultOut						0x12






typedef struct{
	uchar i;
	
}Monitor_Parameters;