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

uartSts_type uartGlobalSts[busIdx_max];
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
    unsigned char uartData;
    busIdx_type i = 0;

    /* test only */
    // S4BUF = 0xaa;
    // S3BUF = 0xaa;
    for(i = 0; i < busIdx_max; i ++)
    {

        if(uartTxFifo_Obj[i].curPtr > 0)
        {

            /* If the Tx FIFO buffer has data to send then put
               the send data into data register
             */
            if(uartGlobalSts != uartSts_busy)
            {
                getFifoData(&uartTxFifo_Obj[i], &uartData);
                if(i == busIdx_public)
                {
                    uartGlobalSts[busIdx_public] = uartSts_busy;
                    P53 = 1;
                    S4BUF = uartData;
                }
                else if(i == busIdx_private)
                {
                    uartGlobalSts[busIdx_private] = uartSts_busy;
                    P52 = 1;
                    S3BUF = uartData;
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

	/* Debug uart channel */
	SCON	=   0x50;	/* 8bit data, baudrate adjustable */
	AUXR	|=  0x40;   /* Fosc cloco frequency for timer1 -> 1T */
	AUXR	&=  0xFE;	/* uart1 choose timer1 as the baud rate generator */
	TMOD	&=  0x0F;	/* set the timer 1 as the 16 bit auto reload operation mode */
	TL1		=   0x8F;	/* set the timer initial value */
	TH1		=   0xFD;	/* set the timer initial value */
	ET1		=   0;		/* inhibit timer 1 interrupt */
	TR1		=   1;		/* start timer 1 */
	ES		=   1;      /* enable uart interrupt */
	
	/* UART 3 Baud Rate:9600, using Timer3 */
	S3CON   = 	0x10;	/* 8 bit data, baudrate adjustable */
	S3CON   |= 	0x40;	/* uart3 use timer 3 as the baudrate generator */
	T4T3M   &= 	0xFD;	/* set the clock frequency as Fosc / 12 -> 12T */
	T3L 	= 	0xCC;	/* set the initial value */
	T3H 	= 	0xFF;	/* set the initial value */
	T4T3M   |= 	0x08;	/* start timer 3 */
    IE2     |=  0x08;   /* enable uart 3 interrupt */
	
	/* UART 4	Baud Rate:9600, using Timer2 */
	S4CON   = 	0x10;	/* 8 bit data, baud rate adjustable */
	S4CON   &= 	0xBF;	/* uart 4 use timer 2 as the baudrate generator */
	AUXR 	&= 	0xFB;	/* set the clock frequency for timer 2 as Fosc /12 -> 12T  */
	T2L 	= 	0xCC;	/* set the initial value */
	T2H 	= 	0xFF;	/* set the initial value */
	AUXR 	|= 	0x10;	/* start timer 2 */
    IE2     |=  0x10;   /* enable uart 4 interrupt */

		
	EA		= 1;        /* start the gloabl interrupt */

    /* Create an FIFO object buffer uart data */
    for(i = 0; i < busIdx_max; i ++)
    {
        uartTxFifo_Obj[i] = fifoInit(UART_DATA_LEN_IN_BYTE);
        uartRxFifo_Obj[i] = fifoInit(UART_DATA_LEN_IN_BYTE);
    }
}

void uartDrvUpdate()
{
    sendDataCyclic();
}

uartSts_type setUartSendBuf(unsigned char *uartData, busIdx_type busId)
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

uartSts_type getUartReceiveBuf(unsigned char *uartData, busIdx_type busId)
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

/* uart 3(private network connect with door controller) interrupt service function */ 
void uart3Int()
{
    /* test only */
    unsigned char testStuff = 0;
    /* TODO this interrupt shoud be copy for two channel */
    unsigned char uartData;
    if (S3CON&S3RI)
    {
        P44 = 1;
        S3CON &= ~S3RI;

        uartData = S3BUF;
        /* Put the data into the Rx FIFO */
        if(uartRxFifo_Obj[busIdx_private].curPtr == 3)
        {
            testStuff ++;
        }                 
		setFifoData(&uartRxFifo_Obj[busIdx_private], &uartData);
        
        P44 = 0;
    }
    if (S3CON&S3TI)
    {
        S3CON &= ~S3TI;
        uartGlobalSts[busIdx_private] = uartSts_normal;
        P52 = 0;         
    }

    
}

/* uart 4(public network connect with PC) interrupt service function */
void uart4Int()
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
        uartGlobalSts[busIdx_public] = uartSts_normal;
        P53 = 0;         
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
