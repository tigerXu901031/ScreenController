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
        - follow the MODBUS protocol format

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

networkInfo_type networkObj;

static void crc16Calc(msgBuf_type *msgObj)
{

}

static unsigned int isCrc16Ok(msgBuf_type *msgObj)
{
    return 1;
}

static void readMsgAssemble(msgBuf_type *msgObj, unsigned char newData, unsigned char *dataByteCnt, busIdx_type busId)
{
    /* 
       Both handle the read request message and read response message:
       
       TODO: to figure out how to distinguish 

       Default read message length is 2 byte except for the higher register address byte 
       was 0x30 
     */
    static unsigned char dataFieldLen = 0;
    static unsigned char serviceType = 0;

    unsigned char currentDataByte = 0;
    unsigned char longFrameRemainLen = 0;

    /* in this switch case the data counter start from the 3rd byte
       end to the start of */
    switch(*dataByteCnt)
    {
        /* 3rd byte */
        case 3:
            /* higher byte of the 16-bit address */
            if(busId == busIdx_public)
            {
                serviceType = SERVICETYPE_READ_REQ;
                msgObj->readReqMsgObj.regAdd[0] = newData;
            }
            else if(newData == 0x30 && busId == busIdx_private)
            {
                serviceType = SERVICETYPE_READ_LONGRESP;
                msgObj->readLongRepMsgObj.regAdd[0] = newData;
            }
            else{
                serviceType = SERVICETYPE_READ_RESP;
                msgObj->readRepMsgObj.regAdd[0] = newData;
            }
            break;

        /* 4th byte */
        case 4:
            if(serviceType == SERVICETYPE_READ_REQ)
            {
                /* lower byte of the 16-bit address */
                msgObj->readReqMsgObj.regAdd[1] = newData;
            }
            else if(serviceType == SERVICETYPE_READ_LONGRESP)
            {
                /* in this case it is the start address from 0 - 19 */
                msgObj->readLongRepMsgObj.regAdd[1] = newData;
            }
            else if(serviceType == SERVICETYPE_READ_RESP)
            {
                /* lower byte of the 16-bit address */
                msgObj->readRepMsgObj.regAdd[1] = newData;
            }
            else{/* unknown error happen */}
            break;

        /* 5th byte */
        case 5:
            if(serviceType == SERVICETYPE_READ_REQ)
            {
                /* in this case it is the lower crc byte */
                msgObj->readReqMsgObj.crc[0] = newData;
            }
            else if(serviceType == SERVICETYPE_READ_LONGRESP)
            {
                /* in this case it is the data length of the following data
                   lengthInByte = (2 ^ value) * 2 */
                msgObj->readLongRepMsgObj.lengthCode = newData;
                dataFieldLen = (2 << newData); 
            }
            else if(serviceType == SERVICETYPE_READ_RESP)
            {   
                /* higher byte of the 1st 16-bit data */
                msgObj->readRepMsgObj.msgData[0] = newData;
            }
            else{/* unknown error happen */}
            break;
        
        /* 6th byte */
        case 6:
            if(serviceType == SERVICETYPE_READ_REQ)
            {
                /* in this case it is the lower crc byte */
                msgObj->readReqMsgObj.crc[1] = newData;

                /* message recieved finished */
                msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = serviceType;
                msgObj->msgByteArray[DATAARRAY_MSGLENGTH_BYTE] = *dataByteCnt;
                *dataByteCnt = 0;
            }
            else if(serviceType == SERVICETYPE_READ_LONGRESP)
            {
                /* lower byte of the 1st 16 bit data */
                msgObj->readLongRepMsgObj.msgData[0] = newData;

            }
            else if(serviceType == SERVICETYPE_READ_RESP)
            {   
                /* lower byte of the 1st 16-bit data */
                msgObj->readRepMsgObj.msgData[1] = newData;
            }
            else{/* unknown error happen */}
            break;

        /* 7th byte */
        case 7:
            if(serviceType == SERVICETYPE_READ_LONGRESP)
            {
                /* lower byte of the 1st 16 bit data */
                msgObj->readLongRepMsgObj.msgData[1] = newData;
            }
            else if(serviceType == SERVICETYPE_READ_RESP)
            {   
                /* lower byte of the 16-bit crc */
                msgObj->readRepMsgObj.crc[0] = newData;
            }
            else{/* unknown error happen */}
            break;

        case 8:
            if(serviceType == SERVICETYPE_READ_LONGRESP)
            {
                /* higher byte of the 2st 16 bit data */
                msgObj->readLongRepMsgObj.msgData[2] = newData;
            }
            else if(serviceType == SERVICETYPE_READ_RESP)
            {   
                /* higher byte of the 16-bit crc */
                msgObj->readRepMsgObj.crc[1] = newData;

                /* message recieve finsihed */
                msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = serviceType;
                msgObj->msgByteArray[DATAARRAY_MSGLENGTH_BYTE] = *dataByteCnt;
                *dataByteCnt = 0;
            }
            else{/* unknown error happen */}
            break;
        
        default:
            
            currentDataByte = *dataByteCnt - 8;
            longFrameRemainLen = dataFieldLen - 3;
            if(serviceType == SERVICETYPE_READ_LONGRESP)
            {
                if(currentDataByte <= longFrameRemainLen)
                {
                    /* When there is long-frame message Add_H = 0x30
                       then construct the other data byte
                       here the index = currentDataByte + 2 means in the
                       last case:8 is has already assigned to the byte #3,
                       hence it will -3 and due to the array was count from 0
                       then its 3-1 = 2 */
                    msgObj->readLongRepMsgObj.msgData[currentDataByte + 2] = newData;
                }
                else if(currentDataByte == longFrameRemainLen + 1)
                {
                    /* lower crc byte */
                    msgObj->readLongRepMsgObj.crc[0] = newData;
                }
                else if (currentDataByte == longFrameRemainLen + 2)
                {
                    /* higher crc byte */
                    msgObj->readLongRepMsgObj.crc[1] = newData;

                    /* last byte recieved set the available status and
                       clear the data byte counter */
                    msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = serviceType;
                    msgObj->msgByteArray[DATAARRAY_MSGLENGTH_BYTE] = *dataByteCnt;
                    *dataByteCnt = 0;
                }
                else
                {
                    /* unknown error */
                }
            }
            else{
                /* unknown error */
            }
    }
}

static void writeOpMsgAssemble(msgBuf_type *msgObj, unsigned char newData,unsigned char *dataByteCnt, busIdx_type busId)
{
    /* Usually when recieved this message after
       an success write operation */
    switch(*dataByteCnt)
    {
        case 3:
            /* higher address byte */
            msgObj->writeAccessMsgObj.regAdd[0] = newData;
            break;
        case 4:
            /* lower address byte */
            msgObj->writeAccessMsgObj.regAdd[1] = newData;
            break;
        case 5:
            /* higher write data byte */
            msgObj->writeAccessMsgObj.msgData[0] = newData;
            break;
        case 6:
            /* lower write data byte */
            msgObj->writeAccessMsgObj.msgData[1] = newData;
            break;
        case 7:
            /* lower crc byte */
            msgObj->writeAccessMsgObj.crc[0] = newData;
            break;
        case 8:
            /* higher crc byte */
            msgObj->writeAccessMsgObj.crc[1] = newData;

            /* message recieved finsih */
            if(busId == busIdx_public)
            {
                msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = SERVICETYPE_WRITE_REQ;
            }
            else if(busId == busIdx_private)
            {
                msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = SERVICETYPE_WRITE_RESP;
            }
            else{/* unknown error */}
            msgObj->msgByteArray[DATAARRAY_MSGLENGTH_BYTE] = *dataByteCnt;
            *dataByteCnt = 0;
            break;
        default:
            /* Error condition */
            break;
    }
}

/* TODO: need to confirme the errVal byte filed are the same or not */
static void accessFailMsgAssemble(msgBuf_type *msgObj, unsigned char newData,unsigned char *dataByteCnt)
{
    switch(*dataByteCnt)
    {
        case 3:
            /* higher address byte */
            msgObj->accessFailRepMsgObj.regAdd[0] = newData;
            break;
        case 4:
            /* lower address byte */
            msgObj->accessFailRepMsgObj.regAdd[1] = newData;
            break;
        case 5:
            /* read or write operation error code */
            msgObj->accessFailRepMsgObj.errVal[0] = newData;
            break;
        case 6:
            /* read or write operation error code */
            msgObj->accessFailRepMsgObj.errVal[1] = newData;
            break;
        case 7:
            /* lower crc byte */
            msgObj->accessFailRepMsgObj.crc[0] = newData;
            break;
        case 8:
            /* higher crc byte */
            msgObj->accessFailRepMsgObj.crc[1] = newData;

            if(msgObj->accessFailRepMsgObj.cmd == MSGCMD_READOPFAIL)
            {
                msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = SERVICETYPE_READ_FAIL;
            }
            else if(msgObj->accessFailRepMsgObj.cmd == MSGCMD_WRITEOPFAIL)
            {
                msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = SERVICETYPE_WRITE_FAIL;
            }
            msgObj->msgByteArray[DATAARRAY_MSGLENGTH_BYTE] = *dataByteCnt;
            *dataByteCnt = 0;
            break;
        default:
            /* unknown error condition */
            break;
    }
}

static void dataMonitorMsgAssemble(msgBuf_type *msgObj, unsigned char newData,unsigned char *dataByteCnt)
{
    /* TBD */
    
}

static void heartBeatMsgAssemble(msgBuf_type *msgObj, unsigned char newData,unsigned char *dataByteCnt)
{
    switch(*dataByteCnt)
    {
        case 3:
            /* heart beat data */
            msgObj->heartBeatMsgObj.val = newData;
            break;
        case 4:
            /* lower crc byte */
            msgObj->heartBeatMsgObj.crc[0] = newData;
            break;
        case 5:
            /* higher crc byte */
            msgObj->heartBeatMsgObj.crc[1] = newData;

            msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = SERVICETYPE_HEART_BEAT;
            msgObj->msgByteArray[DATAARRAY_MSGLENGTH_BYTE] = *dataByteCnt;
            *dataByteCnt = 0;
            break;    
        default:
            /* unknown error condition */
            break;
    }
}

static unsigned char getRxMsgAndAssemble(msgBuf_type *msgObj)
{
    unsigned char isMsgReady = 0;
    static unsigned char dataByteCnt[2] = {0, 0};
    static unsigned char newDatBuf[2];
    static msgBuf_type msgBuf[2];

    busIdx_type i = 0;
    for(i = 0; i < busIdx_max; i ++)
    {
        /* if new data from uart is available */
        if(isUartNewDataAvailable(i))
        {
            dataByteCnt[i] ++;
            getUartReceiveBuf(&newDatBuf[i], i);

            if(dataByteCnt[i] == 1)
            {   
                /* ensure the message buffer is clear */
                clearDataBlock(&msgBuf[i], 50);
                /* node index byte */
                msgBuf[i].msgByteArray[0] = newDatBuf[i];
            }
            else if(dataByteCnt[i] == 2)
            {
                /* command byte */
                msgBuf[i].msgByteArray[1] = newDatBuf[i];
            }
            else
            {
                /* consecutive byte */
                switch(msgBuf[i].msgByteArray[1])
                {
                    case MSGCMD_READOP:
                        readMsgAssemble(&msgBuf[i], newDatBuf[i], &dataByteCnt[i], (busIdx_type)i);
                    break;

                    case MSGCMD_WRITEOP:
                        writeOpMsgAssemble(&msgBuf[i], newDatBuf[i], &dataByteCnt[i], (busIdx_type)i);
                    break;

                    case MSGCMD_READOPFAIL:
                    case MSGCMD_WRITEOPFAIL:
                        accessFailMsgAssemble(&msgBuf[i], newDatBuf[i], &dataByteCnt[i]);
                    break;

                    case MSGCMD_DATAMONITOR:
                        dataMonitorMsgAssemble(&msgBuf[i], newDatBuf[i], &dataByteCnt[i]);
                    break;

                    case MSGCMD_HEARTBEAT:
                        heartBeatMsgAssemble(&msgBuf[i], newDatBuf[i], &dataByteCnt[i]);
                    break;

                    default:
                        /* Might need report error due to no message class
                           is match */
                    break;
                }
            }

            /* if the new message is assembled finished and available,
               if available then output the read buffer
             */
            if(msgBuf[i].msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] != 0)
            {
                /* copy the finished message to the argument */
                /* TODO: comment temporary due to the type error */
                memcpyCus(msgObj, &msgBuf[i], 50);

                /* clear the buffer and wai for the new message */
                clearDataBlock(&msgBuf[i], 50);

                /* set the return value to indicate a message is ready */
                isMsgReady = 1;
            }
            else{
                /* do nothing */
                isMsgReady = 0;
            }
        }
        else
        {
            /* No new data do nothing */
        }
        msgObj ++;
    }
    return isMsgReady;
}

static void setTxMsgAndDisassemble(msgBuf_type *msgObj, busIdx_type busId)
{
    /* convert the general message type into byte sequence in buffer */
    unsigned char i = 0;
    unsigned char *dataPtr = 0;
    dataPtr = &msgObj->msgByteArray[0];

    for(i = 0; i < msgObj->msgByteArray[DATAARRAY_MSGLENGTH_BYTE]; i ++)
    {
        setUartSendBuf(dataPtr, busId);
        dataPtr ++;
    }
}

static void networkGatewayHandler(msgBuf_type *msgObj)
{
    /* 
       All the message recieved from public bus has same the public node id
       will forward to the door controller

       All the message revieved from private bus 
    */
   unsigned char i = 0;
   for(i = 0; i < busIdx_max; i ++)
   {
       if(i == ((unsigned char)busIdx_public) && (msgObj->msgByteArray[0] == networkObj.publicNodeId))
       {
               /* forward the message to the private bus */
               setTxMsgAndDisassemble(msgObj, busIdx_private);
       }
       else if(i == ((unsigned char)busIdx_private) && (msgObj->msgByteArray[0] == networkObj.publicNodeId))
       {
               /* forward the message to the public bus */
               setTxMsgAndDisassemble(msgObj, busIdx_public);
       }
       else
       {
           /* something wrong here */
       }
       msgObj ++;
   }
}

static void rxDataHandler(msgBuf_type *msgObj, networkDataBuf_type *dataBuf)
{
    /* do crc check only for private communication 
    no need the gateway message */
    unsigned char serviceType;
    unsigned char i = 0;

    /* used for long message */
    unsigned char longMsgDataFeildLen = 0;
    unsigned char longMsgAddLowerByte = 0;

    /* check whether the message need to be converted into application data */
    if(msgObj->msgByteArray[0] == networkObj.privateNodeId)
    {
        if(isCrc16Ok(&msgObj))
        {
            serviceType = msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE];
            switch (serviceType)
            {
                case SERVICETYPE_READ_RESP:
                    /* extract cmd, add, data */
                    dataBuf->networkData[0].cmd = MSGCMD_READOP;
                    dataBuf->networkData[0].add[0] = msgObj->readRepMsgObj.regAdd[0];
                    dataBuf->networkData[0].add[1] = msgObj->readRepMsgObj.regAdd[1];
                    dataBuf->networkData[0].opData[0] = msgObj->readRepMsgObj.msgData[0];
                    dataBuf->networkData[0].opData[1] = msgObj->readRepMsgObj.msgData[1];

                    dataBuf->dataLength = 1;
                    break;

                case SERVICETYPE_READ_LONGRESP:
                    longMsgDataFeildLen = (msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] - 7) / 2;
                    longMsgAddLowerByte = msgObj->readLongRepMsgObj.regAdd[1];
                    dataBuf->dataLength = longMsgDataFeildLen;
                    for(i = 0; i < longMsgDataFeildLen; i ++)
                    {
                        dataBuf->networkData[i].cmd = MSGCMD_READOP;

                        dataBuf->networkData[i].add[0] = msgObj->readLongRepMsgObj.regAdd[0];
                        dataBuf->networkData[i].add[1] = longMsgAddLowerByte;

                        dataBuf->networkData[i].opData[0] = msgObj->readLongRepMsgObj.msgData[2*i];
                        dataBuf->networkData[i].opData[1] = msgObj->readLongRepMsgObj.msgData[2*i+1];

                        longMsgAddLowerByte ++;
                    }
                    break;

                case SERVICETYPE_WRITE_RESP:
                    /* check whether the write response equal to the last write
                       request if equal  */
                    dataBuf->dataLength = 1;
                    dataBuf->networkData[0].cmd = MSGCMD_WRITEOP;
                    dataBuf->networkData[0].add[0] = msgObj->writeAccessMsgObj.regAdd[0];
                    dataBuf->networkData[0].add[1] = msgObj->writeAccessMsgObj.regAdd[1];
                    dataBuf->networkData[0].opData[0] = msgObj->writeAccessMsgObj.msgData[0];
                    dataBuf->networkData[0].opData[1] = msgObj->writeAccessMsgObj.msgData[1];
                    break;

                case SERVICETYPE_READ_FAIL:
                    /* check whether the write response equal to the last write
                       request if equal  */
                    dataBuf->dataLength = 1;
                    dataBuf->networkData[0].cmd = MSGCMD_READOPFAIL;
                    dataBuf->networkData[0].add[0] = msgObj->accessFailRepMsgObj.regAdd[0];
                    dataBuf->networkData[0].add[1] = msgObj->accessFailRepMsgObj.regAdd[1];
                    dataBuf->networkData[0].opData[0] = msgObj->accessFailRepMsgObj.errVal[0];
                    dataBuf->networkData[0].opData[1] = msgObj->accessFailRepMsgObj.errVal[1];
                    break;

                case SERVICETYPE_WRITE_FAIL:
                    dataBuf->dataLength = 1;
                    dataBuf->networkData[0].cmd = MSGCMD_WRITEOPFAIL;
                    dataBuf->networkData[0].add[0] = msgObj->accessFailRepMsgObj.regAdd[0];
                    dataBuf->networkData[0].add[1] = msgObj->accessFailRepMsgObj.regAdd[1];
                    dataBuf->networkData[0].opData[0] = msgObj->accessFailRepMsgObj.errVal[0];
                    dataBuf->networkData[0].opData[1] = msgObj->accessFailRepMsgObj.errVal[1];
                    break;
                default:
                    /* error happened */
                    break;
            }
            /*  */
        }
        else{
            /* respond crc error message if needed (ony when R/W request message) */

        } 
    }
    else{

    }
      
}

static void readReqMsgTxPreprocess(msgBuf_type *msgObj, networkDataBuf_type *dataBuf)
{
    /* TODO: now only considering normal 2-byte data read request message
       long frame read request havent been handled */
    msgObj->readReqMsgObj.nodeId = networkObj.privateNodeId;

    msgObj->readReqMsgObj.cmd = dataBuf->networkData[0].cmd;

    msgObj->readReqMsgObj.regAdd[0] = dataBuf->networkData[0].add[0];
    msgObj->readReqMsgObj.regAdd[1] = dataBuf->networkData[0].add[1];

    

    msgObj->msgByteArray[DATAARRAY_MSGLENGTH_BYTE] = 6;
    msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = SERVICETYPE_READ_REQ;

    crc16Calc(msgObj);
}

static void writeReqMsgTxPreprocess(msgBuf_type *msgObj, networkDataBuf_type *dataBuf)
{
    msgObj->writeAccessMsgObj.nodeId = networkObj.privateNodeId;

    msgObj->writeAccessMsgObj.cmd = dataBuf->networkData[0].cmd;

    msgObj->writeAccessMsgObj.regAdd[0] = dataBuf->networkData[0].add[0];
    msgObj->writeAccessMsgObj.regAdd[1] = dataBuf->networkData[0].add[1];

    msgObj->writeAccessMsgObj.msgData[0] = dataBuf->networkData[0].opData[0];
    msgObj->writeAccessMsgObj.msgData[1] = dataBuf->networkData[0].opData[1];

    msgObj->msgByteArray[DATAARRAY_MSGLENGTH_BYTE] = 8;
    msgObj->msgByteArray[DATAARRAY_NEWMSGAVAILABLE_BYTE] = SERVICETYPE_WRITE_REQ;

    crc16Calc(msgObj);
}

static void txDataHandler(msgBuf_type *msgObj, networkDataBuf_type *dataBuf)
{
    /* process the data from application and convert the operational data to message
       1. fill all the operational data to the message
       2. do crc calculation and fill the crc field

        TODO: 
            - need to consider how to remove the read out data and move all the remain
              data one position forward.
            - here just process and send one message each cycle, need to consider whether
              require to handle multiple message each cycle.
            - By default each cycle consume the first networkData array element need to determine 
              how to remove the consumed first element as fifo

       - In this case normal write request 0x06 and read response 0x03
         message will be handled here
    
    */
   if(dataBuf->dataLength > 0)
   {
        switch (dataBuf->networkData[0].cmd)
        {
            case MSGCMD_READOP:
                readReqMsgTxPreprocess(msgObj, dataBuf);
                break;

            case MSGCMD_WRITEOP:
                writeReqMsgTxPreprocess(msgObj, dataBuf);
                break;

            default:
                break;
        }
   }

}


static void rxServiceHandler(msgBuf_type *msgObj)
{

}

static void txServiceHandler(msgBuf_type *msgObj)
{

}

static void fetchNodeId()
{
    networkObj.privateNodeId = 0xff;
    networkObj.publicNodeId = 0x01;
}

void networkInit()
{
    uartDrvInit();



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
    fetchNodeId();
}

void networkUpdate()
{
    uartDrvUpdate();
}

/* 10ms task */
void getNetworkData(networkDataBuf_type *nwDataBuf)
{
    /* Argument *nwDataBuf it's better  
     */
    unsigned char i = 0;
    msgBuf_type rxMsgBuf[busIdx_max];

    /* recieve data in byte and assemble the data byte into message */
    if(getRxMsgAndAssemble(&rxMsgBuf))
    {
        /* TODO: its better to clear the rxMsgBuf after the function
           has already handled this message then the next function
           is no need to do anything */

        /* first forward the message that no need to do anything with it */
        networkGatewayHandler(&rxMsgBuf);

        /* second handle some request by network service and do handle the
           message without the intervene from app
           1. Clear some requst status
           2. Request status timeout and record the error info */
        rxServiceHandler(&rxMsgBuf);

        /* message -> application operational data
           only the private communication need to be handled
           in the application, other messages has already be
           forward by the gateway function */
        rxDataHandler(&rxMsgBuf[busIdx_private], nwDataBuf);
    }
}

/* 10ms task */
void setNetworkData(networkDataBuf_type *nwDataBuf)
{
    msgBuf_type txMsgBuf;
    clearDataBlock(&txMsgBuf, sizeof(txMsgBuf));

    /* test purpose only */
    static unsigned char iCounter = 0;
    /* TODO: 
       1. need to add more logic to handle how to deal
          with multiple data length request in the same
          10ms task cycle. */
          
    /* application operational data -> message */
    txDataHandler(&txMsgBuf, nwDataBuf);

    /* test purpose only */
    clearDataBlock(&txMsgBuf, sizeof(txMsgBuf));
    if(iCounter == 10)
    {
        txMsgBuf.msgByteArray[0] = 0xff;
        txMsgBuf.msgByteArray[1] = 0x03;
        txMsgBuf.msgByteArray[2] = 0x30;
        txMsgBuf.msgByteArray[3] = 0x00;
        txMsgBuf.msgByteArray[4] = 0x00;
        txMsgBuf.msgByteArray[5] = 0x01;
        txMsgBuf.msgByteArray[6] = 0x9e;
        txMsgBuf.msgByteArray[7] = 0xd4;
        txMsgBuf.msgByteArray[DATAARRAY_MSGLENGTH_BYTE] = 0x08;
        P44 = 0;
        iCounter = 0;
    }
    else
    {
        P44 = 1;
        iCounter ++;
    }

    /* TODO:
        1. send the 100ms cyclic system info read request message 
        2. set request status */
    txServiceHandler(&txMsgBuf);

    /* put to the message to the uart send buffer
       each cycle one message */
    setTxMsgAndDisassemble(&txMsgBuf, busIdx_private);
    
}