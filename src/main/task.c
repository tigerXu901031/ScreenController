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

void task1ms()
{

    /* 1ms seems very critial for 8bit send,
       maybe need to increase to 2ms later */
    uartDrvUpdate();
}

unsigned char testSendByte[2] = {0x55, 0xaa};
unsigned char testRecByte[2] = {0, 0};
void task10ms()
{
    static unsigned char iCounter = 0;
    /* some test for FIFO buffer + uart drvier */
    // uartDrvUpdate();


    getUartReceiveBuf(&testRecByte[0],busIdx_public);
    getUartReceiveBuf(&testRecByte[1],busIdx_public);
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
}