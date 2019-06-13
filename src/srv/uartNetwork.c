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
    /* Default read message length is 2 byte
       except for the higher register address
       byte was 0x30 
     */
    static unsigned int dataLen = 2;
    unsigned int crc[2];

    /* increment the data byte counter */
    *dataByteCnt ++;
    
    /* in this switch case the data counter start from the 3rd byte
       end to the start of */
    switch(*dataByteCnt)
    {
        case 3:
            /* higher byte of the 16-bit address */
            msgObj->regAdd[0] = newData;
            
            break;
        case 4:
            /* lower byte of the 16-bit address */
            msgObj->regAdd[1] = newData;
            if(msgObj->regAdd[1] == 0x30)
            {
                dataLen = msgObj->regAdd[1];
            }
            else{
                /* NOP */
            }
            break;
        case 5:
            /* higher byte of the 1st 16-bit data */
            msgObj->data[0] = newData;
            break;
        case 6:
            /* lower byte of the 1st 16-bit data */
            msgObj->data[1] = newData;
            break;
        case 7:
            /* higher byte of the 1st 16-bit data */
            msgObj->data[2] = newData;
            break;

    }

    /* if the current byte counter equals to the last data
       then do the crc calculation and set the new data
       available
     */
    if(dataByteCnt - 4 == dataLen)
    {
        
        crc16(msgObj, *dataByteCnt, &crc);
        msgObj->crc[0] = crc[0];
        msgObj->crc[1] = crc[1];
        msgObj->newMsgAvailable = 1;
        *dataByteCnt = 0;
    }
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

    uartDrvUpdate();
}

void setTxMsgAndDisassemble(msg_type *msgObj)
{
    
}

void getRxMsgAndAssemble(msg_type *MsgObj)
{
    static unsigned int dataByteCnt = 0;
    static unsigned int newDatBuf = 0;
    static msgBuf_type msgBuf[2];

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
                nodeIdConstruct(&msgBuf[i].msg, newDatBuf, &dataByteCnt);
            }
            else if(dataByteCnt == 1)
            {
                /* command byte */
                cmdConstruct(&msgBuf[i].msg, newDatBuf, &dataByteCnt);
                }
            else
            {
                /* consecutive byte */
                switch(msgBuf[i].msg.cmd)
                {
                    case msgClass_readOp:
                        readOpMsgConstruct(&msgBuf[i].msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_readFail:
                        readFailMsgConstruct(&msgBuf[i].msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_writeOp:
                        writeOpMsgConstruct(&msgBuf[i].msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_writeFail:
                        writeFailMsgConstruct(&msgBuf[i].msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_dataMonitor:
                        dataMonitorMsgConstruct(&msgBuf[i].msg, newDatBuf, &dataByteCnt);
                    break;

                    case msgClass_heartBeat:
                        dataMonitorMsgConstruct(&msgBuf[i].msg, newDatBuf, &dataByteCnt);
                    break;

                    default:
                        /* Might need report error due to no message class
                           is match */
                    break;
                }
            }
            /* Check if the new message is assembled finished and available,
               if available then output the read buffer
             */
            if(msgBuf[i].msg.newMsgAvailable == 1)
            {
                memcpy(MsgObj, &msgBuf[i].msg, sizeof(MsgObj));
                /* after copy the data into the read buffer, clear the local
                   static new message available
                 */
                msgBuf[i].msg.newMsgAvailable = 0;
            }
            /* If new message not available then clear  */
            else
            {
                MsgObj->newMsgAvailable = 0;
            }
        }
        else
        {
            /* No new data do nothing */
        }
    }

}

void crc16(unsigned int *dataField, unsigned int len, unsigned int *crcField)
{

}
