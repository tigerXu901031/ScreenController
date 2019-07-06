#ifndef __UARTNETWORK_H__
#define __UARTNETWORK_H__

#include "../drv/uartDrv.h"
#include "parMap.h"
#include "fifo.h"
#include "crc.h"

#define MSGCMD_READOP       0x03
#define MSGCMD_READOPFAIL   0x83
#define MSGCMD_WRITEOP      0x06
#define MSGCMD_WRITEOPFAIL  0x86
#define MSGCMD_DATAMONITOR  0x0B
#define MSGCMD_HEARTBEAT    0x10

#define SERVICETYPE_READ_REQ        1
#define SERVICETYPE_READ_RESP       2
#define SERVICETYPE_READ_LONGREQ    3
#define SERVICETYPE_READ_LONGRESP   4
#define SERVICETYPE_READ_FAIL       5
#define SERVICETYPE_WRITE_REQ       6
#define SERVICETYPE_WRITE_RESP      7
#define SERVICETYPE_WRITE_FAIL      8
#define SERVICETYPE_HEART_BEAT      9

#define DATAARRAY_NEWMSGAVAILABLE_BYTE  49
#define DATAARRAY_MSGLENGTH_BYTE        48

/* Rx on public bus and can be forward to private bus
   Tx on private bus by forward from public bus
   Rx on private bus to request some data */
typedef struct{
    unsigned char nodeId;
    unsigned char cmd;
    unsigned char regAdd[2];
    unsigned char msgData[2];
    unsigned char crc[2];
}readReqMsg_type;

/* Tx on public bus by forward from private bus
   Rx on private bus forward to public bus
   Rx on private bus to display */
typedef struct{
    unsigned char nodeId;
    unsigned char cmd;
    unsigned char regAdd[2];
    unsigned char msgData[2];
    unsigned char crc[2];
}readRepMsg_type;

/* Rx on private bus to display some cyclic(100ms) system information */
typedef struct{
    unsigned char nodeId;
    unsigned char cmd;
    unsigned char lengthCode;
    unsigned char msgData[40];
    unsigned char crc[2];
}readLongRepMsg_type;

/* Tx on public bus by forward from private bus
   Rx on private bus forward to public bus
   Rx on private bus to display */
typedef struct{
    unsigned char nodeId;
    unsigned char cmd;
    unsigned char regAdd[2];
    unsigned char errVal;
    unsigned char crc[2];
}accessFailRepMsg_type;

/* Rx on public bus and can be forward to private bus
   Tx on private bus by forward from public bus
   Tx on private bus to change some data in door controller */
typedef struct{
    unsigned char nodeId;
    unsigned char cmd;
    unsigned char regAdd[2];
    unsigned char msgData[2];
    unsigned char crc[2];
}writeAccessMsg_type;

/* Rx on private bus to check the system alive status
   Tx on private bus to inform the system alive */
typedef struct{
    unsigned char nodeId;
    unsigned char cmd;
    unsigned char val;
    unsigned char crc[2];
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
    unsigned char            msgByteArray[50];       
}msg_type;

typedef struct UARTNETWORK
{
    msg_type        msgArr[3];
    unsigned char   validMsgNum;
}msgBuf_type;


typedef struct{
    unsigned char cmd;
    unsigned char add[2];
    unsigned char opData[2];  
}netWorkData_type;

typedef struct{
    netWorkData_type    networkData[20];
    unsigned char        dataLength;
}networkDataBuf_type;

typedef struct{
    unsigned char srvId;
    unsigned char add[2];
    unsigned char longFrameLen;
}serviceReq_type;

typedef enum{
    reqIdx_readReq,
    reqIdx_writeReq,
    reqIdx_readLongReq,
};

typedef struct{
    unsigned char        publicNodeId;
    unsigned char        privateNodeId;
    serviceReq_type      reqSrv[3];
}networkInfo_type;

extern void networkInit();
extern void network2msUpdate();
extern void network50msUpdate();
extern void longFrameHandler();
extern void getNetworkData(unsigned char addL, unsigned char addH, unsigned char *Ldata, unsigned char *Hdata, unsigned char *cmd, unsigned char *agingCnt);
extern void setNetworkData(unsigned char addL, unsigned char addH, unsigned char *Ldata, unsigned char *Hdata, unsigned char *cmd, unsigned char *agingCnt);

#endif