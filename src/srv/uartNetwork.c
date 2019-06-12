/* 
   -----------------------------------------------------------------------
   Author   - Tiger.Xu
   Date     - 2019.06.08
   Version  - 0.0.1

   Change Notes:
        2019.06.08      Tiger.Xu
        Initial version

        ...             ...
        ...
    
   Description:
        - 2 Channel UART 485 communication network protocol
        - Channel 1: PC <-> LCD
        - Channel 2: LCD <-> Main Controller
   
        - Broadcast Id(PC <-> LCD Controller)： 0x00
        - Private Id(LCD Controller <-> Main Controller) is 0xff 
   -----------------------------------------------------------------------
*/
#include "uartNetwork.h"

static void nodeIdConstruct(msg_type *msgObj, unsigned int newData, unsigned int *dataByteCnt)
{
    msgObj->nodeId = newData;
    *dataByteCnt ++;
}

static void cmdConstruct(msg_type *msgObj, unsigned int newData, unsigned int *dataByteCnt)
{
    msgObj->cmd = newData;
    *dataByteCnt ++;
}

static void readOpMsgConstruct(msg_type *msgObj, unsigned int newData, unsigned int *dataByteCnt)
{
    /*  */
}

static void readFailMsgConstruct(msg_type *msgObj, unsigned int newData,unsigned int *dataByteCnt)
{
    
}

static void writeOpMsgConstruct(msg_type *msgObj, unsigned int newData,unsigned int *dataByteCnt)
{
    
}

static void writeFailMsgConstruct(msg_type *msgObj, unsigned int newData,unsigned int *dataByteCnt)
{
    
}

static void dataMonitorMsgConstruct(msg_type *msgObj, unsigned int newData,unsigned int *dataByteCnt)
{
    
}

static void heartBeatMsgConstruct(msg_type *msgObj, unsigned int newData,unsigned int *dataByteCnt)
{
    
}

static void networkGateway()
{
    
}

void networkInit()
{
    uartInit();

    /* TODO:
       Fetch the public node ID from the door controller 
       if the fetch operation is failed then the initialization
       will fail 
       Fetch Node ID procedure:
       1. Send an read (public ID) request to the main controller
       2. 
    */
    
}

void networkUpdate()
{
    networkGateway();
}

void setTxMsgAndDisassemble()
{
    
}

void getRxMsgAndAssemble()
{
    static unsigned int dataByteCnt = 0;
    static unsigned int newDatBuf = 0;
    static msgBuf_type msgBuf;

    networkChannel_type i = 0;
    for(i = 0; i < max_networkChannel; i ++)
    {
        /* if new data from uart is available */
        if(isUartNewDataAvailable(i))
        {
            getUartReceiveBuf(&newDatBuf, i);

            if(dataByteCnt == 0)
            {
                /* node index byte */
                nodeIdConstruct(&msgBuf.msg, newDatBuf, &dataByteCnt);
            }
            else if(dataByteCnt == 1)
            {
                /* command byte */
                cmdConstruct(&msgBuf.msg, newDatBuf, &dataByteCnt);
                }
                else
            {
                /* consecutive byte */
                switch(msgBuf.msg.cmd)
                {
                    case msgClass_readOp:
                        readOpMsgConstruct(&msgBuf.msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_readFail:
                        readFailMsgConstruct(&msgBuf.msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_writeOp:
                        writeOpMsgConstruct(&msgBuf.msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_writeFail:
                        writeFailMsgConstruct(&msgBuf.msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_dataMonitor:
                        dataMonitorMsgConstruct(&msgBuf.msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_heartBeat:
                        dataMonitorMsgConstruct(&msgBuf.msg, newDatBuf, &dataByteCnt);
                    break;

                    default:
                        /* Might need report error due to no message class
                           is match */
                    break;
                }
            }
        }
        else
        {
            /* No new data do nothing */
        }
    }

}

void crc16()
{

}
