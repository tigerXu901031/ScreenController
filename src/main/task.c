#include "task.h"

void taskInit()
{
    IO_INIT();
    delay_ms(200);
    INIT_LCD();
    clear_screen();

    /* need to consider to use cyclic task or not */

    P52 = 0;
    P53 = 0;
    networkInit();
    timerInit();
    timer10ms_Enable();
    timer1ms_Enable();
}

/* test purpose only */
const unsigned char testReadReqMsg[6] = {0x01, 0x03, 0xF1, 0x02, 0x11, 0x22};
const unsigned char testReadRepMsg[8] = {0xFF, 0x03, 0xF2, 0x02, 0xAA, 0x55, 0x23, 0x33};

void task1ms()
{

    static unsigned char testCnt = 0;
    /* test purpose only
       to simulate an test message that set in the FIFO buffer cyclic */
    if(testCnt < sizeof(testReadRepMsg))
    {
        setFifoData(&uartRxFifo_Obj[busIdx_private], &testReadRepMsg[testCnt]);
        testCnt ++;
    }
    else
    {
        testCnt = 0;
    }
    
    /* 1ms send out data via uart seems very critial for 8bit send,
       maybe need to increase to 2ms later
       TODO: now its 2ms ---  */
    networkUpdate();
}

/* test purpose only */
unsigned char testSendByte[2] = {0x55, 0xaa};
unsigned char testRecByte[2] = {0, 0};

void task10ms()
{
    /* test purpose only */
    static networkDataBuf_type testNwData;
    static unsigned char iCounter = 0;
    /* some test for FIFO buffer + uart drvier */
    // getUartReceiveBuf(&testRecByte[0],busIdx_public);
    // getUartReceiveBuf(&testRecByte[1],busIdx_public);
    // setUartSendBuf(&testSendByte[0], busIdx_public);
    // setUartSendBuf(&testSendByte[1], busIdx_public);
    if(iCounter == 0)
    {
        P44 = 0;
        iCounter ++;
    }
    else
    {
        P44 = 1;
        iCounter --;
    }

    getNetworkData(&testNwData);

    // setNetworkData(&testNwData);


}