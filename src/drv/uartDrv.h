#ifndef __UARTDRV_H__
#define __UARTDRV_H_+

#include "STC8.h"
#include "../srv/fifo.h"

#define UART_DATA_LEN_IN_BYTE   1

typedef enum uartSts{
    uartSts_normal,
    uartSts_sendFail,
    uartSts_receiveFail,
    uartSts_timeout,
    uartSts_busy,
}uartSts_type;

typedef enum{
    busIdx_public = 0,
    busIdx_private,
    busIdx_max,
}busIdx_type;

extern void uartInit();
extern void uartDrvUpdate();
extern uartSts_type setUartSendBuf(unsigned int *data, busIdx_type nwChn);
extern uartSts_type getUartReceiveBuf(unsigned int *data, busIdx_type nwChn);
extern unsigned char isUartNewDataAvailable(busIdx_type nwChn);

#endif