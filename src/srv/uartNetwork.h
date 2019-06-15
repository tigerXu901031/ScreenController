#ifndef __UARTNETWORK_H__
#define __UARTNETWORK_H__

#include "../drv/uartDrv.h"
#include "fifo.h"

#define MSGCMD_READOP       0x03
#define MSGCMD_READOPFAIL   0x83
#define MSGCMD_WRITEOP      0x06
#define MSGCMD_WRITEOPFAIL  0x86
#define MSGCMD_DATAMONITOR  0x0B
#define MSGCMD_HEARTBEAT    0x10

#define SERVICETYPE_READ_REQ        0
#define SERVICETYPE_READ_RESP       1
#define SERVICETYPE_READ_LONGREQ    2
#define SERVICETYPE_READ_LONGRESP   3
#define SERVICETYPE_READ_FAIL       4
#define SERVICETYPE_WRITE_REQ       5
#define SERVICETYPE_WRITE_RESP      6
#define SERVICETYPE_WRITE_FAIL      7
#define SERVICETYPE_HEART_BEAT      8

#define DATAARRAY_NEWMSGAVAILABLE_BYTE  49
#define DATAARRAY_MSGLENGTH_BYTE        48

/* Rx on public bus and can be forward to private bus
   Tx on private bus by forward from public bus
   Rx on private bus to request some data */
typedef struct{
    unsigned int nodeId;
    unsigned int cmd;
    unsigned int regAdd[2];
    unsigned int crc[2];
}readReqMsg_type;

/* Tx on public bus by forward from private bus
   Rx on private bus forward to public bus
   Rx on private bus to display */
typedef struct{
    unsigned int nodeId;
    unsigned int cmd;
    unsigned int regAdd[2];
    unsigned int data[2];
    unsigned int crc[2];
}readRepMsg_type;

/* Rx on private bus to display some cyclic(100ms) system information */
typedef struct{
    unsigned int nodeId;
    unsigned int cmd;
    unsigned int regAdd[2];
    unsigned int lengthCode;
    unsigned int data[40];
    unsigned int crc[2];
}readLongRepMsg_type;

/* Tx on public bus by forward from private bus
   Rx on private bus forward to public bus
   Rx on private bus to display */
typedef struct{
    unsigned int nodeId;
    unsigned int cmd;
    unsigned int regAdd[2];
    unsigned int errVal[2];
    unsigned int crc[2];
}accessFailRepMsg_type;

/* Rx on public bus and can be forward to private bus
   Tx on private bus by forward from public bus
   Tx on private bus to change some data in door controller */
typedef struct{
    unsigned int nodeId;
    unsigned int cmd;
    unsigned int regAdd[2];
    unsigned int data[2];
    unsigned int crc[2];
}writeAccessMsg_type;

// /* Tx on public bus by forward from private bus
//    Rx on private bus forward to public bus
//    Rx on private bus to display */
// typedef struct{
//     unsigned int nodeId;
//     unsigned int cmd;
//     unsigned int regAdd[2];
//     unsigned int data[2];
//     unsigned int crc[2];
// }writeRepMsg_type;

/* Tx on public bus by forward from private bus
   Rx on private bus forward to public bus
   Rx on private bus to display */
// typedef struct{
//     unsigned int nodeId;
//     unsigned int cmd;
//     unsigned int regAdd[2];
//     unsigned int errVal[2];
//     unsigned int crc[2];
// }writeFailRepMsg_type;

/* Rx on private bus to check the system alive status
   Tx on private bus to inform the system alive */
typedef struct{
    unsigned int nodeId;
    unsigned int cmd;
    unsigned int val;
    unsigned int crc[2];
}heartBeatMsg_type;

typedef union{
    readReqMsg_type         readReqMsgObj;
    readRepMsg_type         readRepMsgObj;
    readLongRepMsg_type     readLongRepMsgObj;
    accessFailRepMsg_type   accessFailRepMsgObj;
    writeAccessMsg_type     writeAccessMsgObj;
    heartBeatMsg_type       heartBeatMsgObj;
    /* the 50th byte indicate new message available
       the 49th byte indicate total data length  */
    unsigned int            msgByteArray[50];       
}msgBuf_type;

typedef struct{
    unsigned int cmd;
    unsigned int add[2];
    unsigned int data[2];  
}netWorkData_type;

typedef struct{
    netWorkData_type    networkData[20];
    unsigned int        dataLength;
}networkDataBuf_type;

typedef struct{
    unsigned int        publicNodeId;
    unsigned int        privateNodeId;
    networkDataBuf_type reqBuf[5];
    networkDataBuf_type repBuf[5];
}networkInfo_type;

extern void networkInit();
extern void networkUpdate();
extern void getNetworkData(networkDataBuf_type *nwDataBuf);
extern void setNetworkData(networkDataBuf_type *nwDataBuf);

#endif