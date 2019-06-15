#include "task.h"

unsigned char testRecByte = 0;

void taskInit()
{
    // IO_INIT();

    // delay_ms(200);

    // INIT_LCD();

    // clear_screen();

    /* need to consider to use cyclic task or not */

    P52 = 0;
    networkInit();

    // timerInit();

    
    // timer10ms_Enable();

    // timer1ms_Enable();
}

void task1ms()
{
    uartDrvUpdate();
}

void task10ms()
{

    getUartReceiveBuf(&testRecByte,busIdx_private);

    setUartSendBuf(&testRecByte, busIdx_private);
}