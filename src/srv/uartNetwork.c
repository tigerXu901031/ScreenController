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
        - Public Id: 0x01 - 0xfe
        - Private Id(LCD Controller <-> Main Controller) is 0xff

        - All the message recieved from PC public bus which use
          the right id should forward to the door controller
        - All the message recieved from door controller use the
          public id should be forward to 
   -----------------------------------------------------------------------
*/
#include "uartNetwork.h"

static void crc16(unsigned int *dataField, unsigned int len, unsigned int *crcField)
{

}

static unsigned isCrcCheckOk()
{

}

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

static void readMsgConstruct(msg_type *msgObj, unsigned int newData, unsigned int *dataByteCnt)
{
    /* 
       Both handle the read request message and read response message:
       
       TODO: to figure out how to distinguish 

       Default read message length is 2 byte except for the higher register address byte 
       was 0x30 
     */
    static unsigned int dataLen = 2;

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
                /* data length equal to 2 ^ ValOfthisByte */
                dataLen = 2 << msgObj->regAdd[1];
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
        default:
            unsigned int currentDataByte = *dataByteCnt - 7;
            unsigned int longFrameRemainLen = dataLen - 2;
            if(currentDataByte <= longFrameRemainLen)
            {
                /* When there is long-frame message Add_H = 0x30
                   then construct the other data byte */
                msgObj->data[longFrameRemainLen] = newData;
            }
            else if(currentDataByte == longFrameRemainLen + 1)
            {
                /* TODO: ?lower? crc byte */
                msgObj->crc[0] = newData;
            }
            else if (currentDataByte == longFrameRemainLen + 2)
            {
                /* TODO: ?higher? crc byte */
                msgObj->crc[1] = newData;

                /* last byte recieved set the available status and
                   clear the data byte counter */
                msgObj->newMsgAvailable = 1;
                *dataByteCnt = 0;
            }
            else
            {
                /* Error condition */
            }
    }
}

static void writeOpMsgConstruct(msg_type *msgObj, unsigned int newData,unsigned int *dataByteCnt)
{
    /* Usually when recieved this message after
       an success write operation */
    dataByteCnt ++;
    switch(*dataByteCnt)
    {
        case 3:
            /* higher address byte */
            msgObj->regAdd[0] = newData;
            break;
        case 4:
            /* lower address byte */
            msgObj->regAdd[1] = newData;
            break;
        case 5:
            /* higher write data byte */
            msgObj->data[0] = newData;
            break;
        case 6:
            /* lower write data byte */
            msgObj->data[1] = newData;
            break;
        case 7:
            /* lower crc byte */
            msgObj->crc[0] = newData;
            break;
        case 8:
            /* higher crc byte */
            msgObj->crc[1] = newData;

            msgObj->newMsgAvailable = 1;
            *dataByteCnt = 0;
            break;
        default:
            /* Error condition */
            break;
    }
}

static void accessFailMsgConstruct(msg_type *msgObj, unsigned int newData,unsigned int *dataByteCnt)
{
    *dataByteCnt ++;
    switch(*dataByteCnt)
    {
        case 3:
            /* higher address byte */
            msgObj->regAdd[0] = newData;
            break;
        case 4:
            /* lower address byte */
            msgObj->regAdd[1] = newData;
            break;
        case 5:
            /* read or write operation error code */
            msgObj->data[0] = newData;
            break;
        case 6:
            /* lower crc byte */
            msgObj->crc[0] = newData;
            break;
        case 7:
            /* higher crc byte */
            msgObj->crc[1] = newData;

            msgObj->newMsgAvailable = 1;
            *dataByteCnt = 0;
            break;
        default:
            /* Error condition */
            break;
    }
}

static void dataMonitorMsgConstruct(msg_type *msgObj, unsigned int newData,unsigned int *dataByteCnt)
{
    /* TBD */
    
}

static void heartBeatMsgConstruct(msg_type *msgObj, unsigned int newData,unsigned int *dataByteCnt)
{
    *dataByteCnt ++;
    switch(*dataByteCnt)
    {
        case 3:
            /* heart beat data */
            msgObj->data[0] = newData;
        case 4:
            /* lower crc byte */
            msgObj->crc[0] = newData;
            break;
        case 5:
            /* higher crc byte */
            msgObj->crc[1] = newData;

            msgObj->newMsgAvailable = 1;
            *dataByteCnt = 0;
            break;    
    }
}

static void setTxMsgAndDisassemble(msg_type *msgObj)
{
    
}

/* TODO need to determine how the argument to handle two
   message from two network channel at same time */
static void getRxMsgAndAssemble(msg_type *msgObj)
{
    static unsigned int dataByteCnt[2];
    static unsigned int newDatBuf[2];
    static msgBuf_type msgBuf[2];

    busIdx_type i = 0;
    for(i = 0; i < busIdx_max; i ++, msgObj ++)
    {
        /* if new data from uart is available */
        if(isUartNewDataAvailable(i))
        {
            getUartReceiveBuf(&newDatBuf[i], i);

            if(dataByteCnt[i] == 0)
            {
                /* node index byte */
                nodeIdConstruct(&msgBuf[i].msg, newDatBuf[i], &dataByteCnt[i]);
            }
            else if(dataByteCnt[i] == 1)
            {
                /* command byte */
                cmdConstruct(&msgBuf[i].msg, newDatBuf[i], &dataByteCnt[i]);
                }
            else
            {
                /* consecutive byte */
                switch(msgBuf[i].msg.cmd)
                {
                    case msgClass_readOp:
                        readResponseMsgConstruct(&msgBuf[i].msg, newDatBuf[i], &dataByteCnt[i]);
                    break;

                    case msgClass_writeOp:
                        writeOpMsgConstruct(&msgBuf[i].msg, newDatBuf[i], &dataByteCnt[i]);
                    break;

                    case msgClass_readFail:
                    case msgClass_writeFail:
                        accessFailMsgConstruct(&msgBuf[i].msg, newDatBuf[i], &dataByteCnt[i]);
                    break;

                    case msgClass_dataMonitor:
                        dataMonitorMsgConstruct(&msgBuf[i].msg, newDatBuf[i], &dataByteCnt[i]);
                    break;

                    case msgClass_heartBeat:
                        dataMonitorMsgConstruct(&msgBuf[i].msg, newDatBuf[i], &dataByteCnt[i]);
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
                memcpy(msgObj, &msgBuf[i].msg, sizeof(msgBuf[i].msg));
                /* after copy the data into the read buffer, clear the local
                   static new message available
                 */
                msgBuf[i].msg.newMsgAvailable = 0;
            }
            /* If new message not available then clear  */
            else
            {
                msgObj->newMsgAvailable = 0;
            }
        }
        else
        {
            /* No new data do nothing */
        }
    }

}

static void networkGateway(msg_type *msgObj)
{
    /* All the message recieved from public bus satisfied the node id
       will forward to the door controller
       All the message revieved from private bus 
    */
   unsigned int i = 0;
   for(i = 0; i < busIdx_max; )
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
       2. Recieve the valid id and then regard this aid as the public
          id at this operation cycle.
       3. If the ID is not valid or if the ID was not received then
          set an fail status and stay in the init phase
    */
    
}

static void RxDataProcess()
{
    /* clear some  */
}

/* 10ms task */
void getNetworkData()
{
    msg_type rxMsgBuf[busIdx_max];
    /* recieve message */
    getRxMsgAndAssemble(&rxMsgBuf);

    networkGateway(&rxMsgBuf);

    /* do crc check */
    if(isCrcCheckOk())
    {
        /* process message and get the useful data to the screen display */
        RxDataProcess();
    }
    else{
        /*  */
    }
}

/* 10ms task */
void setNetworkData()
{
    
}