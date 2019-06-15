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
        - Use one level fifo buffer when receive and transmit data in byte
          level
        - Baud rate: 9600bps
        - one start bit, one stop bit, 8 data bit
        
   -----------------------------------------------------------------------
*/

#include "uartDrv.h"

uartSts_type uartGlobalSts;
fifo_type uartTxFifo_Obj[busIdx_max];
fifo_type uartRxFifo_Obj[busIdx_max];



// void switch485Mode(busIdx_type busId, busMode_type busMode)
// {
//     if(busId == busIdx_private)
//     {
//         if(busMode == busMode_tx)
//         {
            
//         }
//     }
//     else if(busId == busIdx_public)
//     {
        
//     }
// }

/* This function should be called cyclic in TODO: 1 ms
   (Not final decided yet) and will be called in a timer
   interrupt
 */
static void sendDataCyclic()
{
    unsigned int uartData;
    busIdx_type i = 0;

    P52 = 1;

    for(i = 0; i < busIdx_max; i ++)
    {
        /* test only */
        S3BUF = 0xaa;
        if(uartTxFifo_Obj[i].curPtr > 0)
        {

            /* If the Tx FIFO buffer has data to send then put
               the send data into data register
             */
            if(uartGlobalSts != uartSts_busy)
            {
                uartGlobalSts = uartSts_busy;
                getFifoData(&uartTxFifo_Obj[i], &uartData);
                if(i == busIdx_public)
                {
                    S4BUF = uartData;
                }
                else if(i == busIdx_private)
                {
                    // S3BUF = uartData;
                }
                else{
                    /* unknown error */
                }
            }
            else{
                /* do nothing */
            }
        }
    }
}

void uartDrvInit()
{
    unsigned char i;

	//UART 1
	SCON	= 0x50;		//8λ����,�ɱ䲨����
	AUXR	|= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR	&= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD	&= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1		= 0x8F;		//�趨��ʱ��ֵ
	TH1		= 0xFD;		//�趨��ʱ��ֵ
	ET1		= 0;		//��ֹ��ʱ��1�ж�
	TR1		= 1;		//������ʱ��1
	ES		= 1;                  /*�򿪴����ж�*/
	
	//UART 2
	//reserved
	
	//UART 3 Baud Rate:9600, using Timer3
	S3CON = 	0x10;		//8λ����,�ɱ䲨����
	S3CON |= 	0x40;		//����3ѡ��ʱ��3Ϊ�����ʷ�����
	T4T3M &= 	0xFD;		//��ʱ��3ʱ��ΪFosc/12,��12T
	T3L 	= 	0xCC;		//�趨��ʱ��ֵ
	T3H 	= 	0xFF;		//�趨��ʱ��ֵ
	T4T3M |= 	0x08;		//������ʱ��3
	
	//UART 4					Baud Rate:9600, using Timer2
	S4CON = 	0x10;		//8λ����,�ɱ䲨����
	S4CON &= 	0xBF;		//����4ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR 	&= 	0xFB;		//��ʱ��2ʱ��ΪFosc/12,��12T
	T2L 	= 	0xCC;		//�趨��ʱ��ֵ
	T2H 	= 	0xFF;		//�趨��ʱ��ֵ
	AUXR 	|= 	0x10;		//������ʱ��2
		
	EA		= 1;                  /*�����ж�*/

    /* Create an FIFO object buffer uart data */
    for(i = 0; i < busIdx_max; i ++)
    {
        uartTxFifo_Obj[i] = fifoInit(UART_DATA_LEN_IN_BYTE);
    }
}

void uartDrvUpdate()
{
    sendDataCyclic();
}

uartSts_type setUartSendBuf(unsigned int *uartData, busIdx_type busId)
{
    fifoSts_type writeOpsts;
    uartSts_type returnVal;


    /* write the data into the send buffer */
    writeOpsts = setFifoData(&uartTxFifo_Obj[busId], uartData);
    if(writeOpsts == writeSuccess)
    {
        returnVal = uartSts_normal;
    }
    else{
        returnVal = uartSts_sendFail; 
    }
    return returnVal;
}

uartSts_type getUartReceiveBuf(unsigned int *uartData, busIdx_type busId)
{
    fifoSts_type readOpsts;
    uartSts_type returnVal;

    /* Get the data from Rx fifo */
    readOpsts = getFifoData(&uartRxFifo_Obj[busId], uartData);

    if(readOpsts == readSuccess)
    {
        returnVal = uartSts_normal;
    }
    else{
        returnVal = uartSts_receiveFail;
    }
    return returnVal;
}

void uart3Int() /* uart 3(private network connect with door controller) interrupt service function */ 
{
    /* TODO this interrupt shoud be copy for two channel */
    unsigned char uartData;
    if (S3CON&S3RI)
    {
        S3CON &= ~S3RI;

        uartData = S3BUF;
        /* Put the data into the Rx FIFO */                 
		setFifoData(&uartRxFifo_Obj[busIdx_private], &uartData);
    }
    if (S3CON&S3TI)
    {
        S3CON &= ~S3TI;
        uartGlobalSts = uartSts_normal;                 
    }

    P52 = 0;
}

void uart4Int() /* uart 4(public network connect with PC) interrupt service function */ 
{
    unsigned char uartData;
    if (S4CON&S4RI)
    {
        S4CON &= ~S4RI;

        uartData = S4BUF;
        /* Put the data into the Rx FIFO */                 
		setFifoData(&uartRxFifo_Obj[busIdx_public], &uartData);
    }
    if (S4CON&S4TI)
    {
        S4CON &= ~S4TI;
        uartGlobalSts = uartSts_normal;                 
    }

}

unsigned char isUartNewDataAvailable(busIdx_type nwChn)
{
    if(uartRxFifo_Obj[nwChn].curPtr > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
