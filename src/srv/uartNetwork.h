#ifndef __UARTNETWORK_H__
#define __UARTNETWORK_H__

#include "../drv/uartDrv.h"

typedef enum msgClass_tag{
    msgClass_readOp         = 0x03,
    msgClass_readFail       = 0x83,
    msgClass_writeOp        = 0x06,
    msgClass_writeFail      = 0x86,
    msgClass_dataMonitor    = 0x0B,
    msgClass_heartBeat      = 0x10, 
}msgClass_type;

typedef struct{
    unsigned int newMsgAvailable;
    unsigned int nodeId;
    msgClass_type cmd;
    unsigned int regAdd[2];
    unsigned int data[16];
    unsigned int crc[2];
}msg_type;

typedef union{
    msg_type msg;
    unsigned int msgFull[23];
}msgBuf_type;

extern void networkInit();
extern void networkUpdate();

#endif