#ifndef __UARTDRV_H__
#define __UARTDRV_H__

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
    busIdx_public,
    busIdx_private,
    busIdx_max,
}busIdx_type;

typedef enum{
    busMode_tx,
    busMode_rx,
}busMode_type;


extern void uartDrvInit();
extern void uartDrvUpdate();
extern uartSts_type setUartSendBuf(unsigned int *uartData, busIdx_type nwChn);
extern uartSts_type getUartReceiveBuf(unsigned int *uartData, busIdx_type nwChn);
extern unsigned char isUartNewDataAvailable(busIdx_type nwChn);
extern void uart3Int();
extern void uart4Int();

#endif