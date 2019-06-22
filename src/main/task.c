#include "task.h"

SystemStatusType SysStatus;

void taskInit()
{
    IO_INIT();
    delay_ms(200);
    INIT_LCD();
    clear_screen();
	SysStatusInit(SysStatus);

    /* need to consider to use cyclic task or not */

    P52 = 0;		//RS485_DR_1
    P53 = 0;		//RS485_DR_2
    networkInit();
    timerInit();
    timer10ms_Enable();
    timer1ms_Enable();
}

/* test purpose only */
const unsigned char testReadReqMsg[6] = {0x01, 0x03, 0xF1, 0x02, 0x11, 0x22};
const unsigned char testReadRepMsg[8] = {0xFF, 0x03, 0xF2, 0x02, 0xAA, 0x55, 0x23, 0x33};
const unsigned char testReadLongRepMsg[39] = {0xFF, 0x03, 0x30, 0x00, 0x04, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                              0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                              0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
                                              0x29, 0x30, 0x31, 0x32, 0xcc, 0xcc};
const unsigned char testWriteRepMsg[8] = {0x01, 0x06, 0xF0, 0x99, 0x32, 0x55, 0x55, 0xAA};
const unsigned char testReadFailMsg[8] = {0xFF, 0x83, 0xF0, 0x99, 0x88, 0x55, 0x55, 0xAA};
void task1ms()
{

    // static unsigned char testCnt = 0;
    /* test purpose only
       to simulate an test message that set in the FIFO buffer cyclic */
    // if(testCnt < sizeof(testReadFailMsg))
    // {
    //     setFifoData(&uartRxFifo_Obj[busIdx_private], &testReadFailMsg[testCnt]);
    //     testCnt ++;
    // }
    // else
    // {
    //     testCnt = 0;
    // }

    /* 1ms send out data via uart seems very critial for 8bit send,
       maybe need to increase to 2ms later
       TODO: now its 2ms ---  */
    network2msUpdate();

}

/* test purpose only */
unsigned char testSendByte[2] = {0x55, 0xaa};
unsigned char testRecByte[2] = {0, 0};

InterfaceData_type testPar[20];

void task10ms()
{

    /* test purpose only */

    // static unsigned char iCounter = 0;

    // unsigned char i = 0;
    // unsigned char tempData = 0;
    // /* test code --- echo whatever it recieved at the same bus */
    // for(i = 0; i < uartRxFifo_Obj[1].curPtr; i ++)
    // {
    //     getFifoData(&uartRxFifo_Obj[1], &tempData);
    //     setFifoData(&uartTxFifo_Obj[1], &tempData);
    // }

    // if(iCounter == 10)
    // {
    //     testSetNwData.dataLength =1;
    //     testSetNwData.networkData[0].cmd = 0x03;
    //     testSetNwData.networkData[0].add[0] = 0x00;
    //     testSetNwData.networkData[0].add[1] = 0x04;
    //     P44 = 0;
    //     iCounter = 0;
    // }
    // else
    // {
    //     P44 = 1;
    //     iCounter ++;
    // }
    // unsigned char dummyAgingCnt = 0;
    // getNetworkData(testPar[0].add[1], testPar[0].add[0], &testPar[0].opData[0], &testPar[0].opData[1], &testPar[0].cmd, &dummyAgingCnt);
    // getNetworkData(testPar[1].add[1], testPar[1].add[0], &testPar[1].opData[0], &testPar[1].opData[1], testPar[1].cmd);
    // getNetworkData(testPar[2].add[1], testPar[2].add[0], &testPar[2].opData[0], &testPar[2].opData[1], testPar[2].cmd);
    // getNetworkData(testPar[3].add[1], testPar[3].add[0], &testPar[3].opData[0], &testPar[3].opData[1], testPar[3].cmd);
    // getNetworkData(testPar[4].add[1], testPar[4].add[0], &testPar[4].opData[0], &testPar[4].opData[1], testPar[4].cmd);
    // getNetworkData(testPar[5].add[1], testPar[5].add[0], &testPar[5].opData[0], &testPar[5].opData[1], testPar[5].cmd);
    // getNetworkData(testPar[6].add[1], testPar[6].add[0], &testPar[6].opData[0], &testPar[6].opData[1], testPar[6].cmd);
    // getNetworkData(testPar[7].add[1], testPar[7].add[0], &testPar[7].opData[0], &testPar[7].opData[1], testPar[7].cmd);
    // getNetworkData(testPar[8].add[1], testPar[8].add[0], &testPar[8].opData[0], &testPar[8].opData[1], testPar[8].cmd);
    // getNetworkData(testPar[9].add[1], testPar[9].add[0], &testPar[9].opData[0], &testPar[9].opData[1], testPar[9].cmd);
    // getNetworkData(testPar[10].add[1], testPar[10].add[0], &testPar[10].opData[0], &testPar[10].opData[1], testPar[10].cmd);
    // getNetworkData(testPar[11].add[1], testPar[11].add[0], &testPar[11].opData[0], &testPar[11].opData[1], testPar[11].cmd);
    // getNetworkData(testPar[12].add[1], testPar[12].add[0], &testPar[12].opData[0], &testPar[12].opData[1], testPar[12].cmd);
    // getNetworkData(testPar[13].add[1], testPar[13].add[0], &testPar[13].opData[0], &testPar[13].opData[1], testPar[13].cmd);
    // getNetworkData(testPar[14].add[1], testPar[14].add[0], &testPar[14].opData[0], &testPar[14].opData[1], testPar[14].cmd);
    // getNetworkData(testPar[15].add[1], testPar[15].add[0], &testPar[15].opData[0], &testPar[15].opData[1], testPar[15].cmd);
    // getNetworkData(testPar[16].add[1], testPar[16].add[0], &testPar[16].opData[0], &testPar[16].opData[1], testPar[16].cmd);
    // getNetworkData(testPar[17].add[1], testPar[17].add[0], &testPar[17].opData[0], &testPar[17].opData[1], testPar[17].cmd);
    // getNetworkData(testPar[18].add[1], testPar[18].add[0], &testPar[18].opData[0], &testPar[18].opData[1], testPar[18].cmd);
    // getNetworkData(testPar[19].add[1], testPar[19].add[0], &testPar[19].opData[0], &testPar[19].opData[1], testPar[19].cmd);


    network10msUpdate();

    AppFunRun();		//application program

    // setNetworkData(&testSetNwData);

	
}