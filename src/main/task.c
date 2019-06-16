#include "task.h"

unsigned char testRecByte = 0;

void taskInit()
{
    IO_INIT();
    delay_ms(200);
    INIT_LCD();
    clear_screen();

    /* need to consider to use cyclic task or not */

    P52 = 0;
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

void task10ms()
{
    // getUartReceiveBuf(&testRecByte,busIdx_private);
    // setUartSendBuf(&testRecByte, busIdx_private);
    // uartDrvUpdate();

    static unsigned char iCounter = 0;
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