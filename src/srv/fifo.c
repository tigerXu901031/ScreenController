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
        Generic FIFO(First In First Out) library
   -----------------------------------------------------------------------
*/
#include "fifo.h"

void clearDataBlock(unsigned char *startAdd, unsigned char length)
{
    unsigned int i = 0;
    for(i = 0; i < length; i ++)
    {
        *startAdd = 0x00;
        startAdd ++;
    }
}

void memcpyCus(unsigned char *destAdd,unsigned char *sourceAdd, unsigned char length)
{
    unsigned char i = 0;
    for(i = 0; i < length; i ++)
    {
        *destAdd = *sourceAdd;
        destAdd ++;
        sourceAdd ++;
    }
}

fifo_type fifoInit(unsigned char unitLen)
{
    fifo_type fifoObj;
    fifoObj.unitLen = unitLen;

    /* set the initial current data pointer at 0 */
    fifoObj.curPtr = 0;

    /* clear all the data area */
    clearDataBlock(&fifoObj.fifoData[0], FIFO_MAX_LENGTH);

    return fifoObj;
}

fifoSts_type getFifoData(fifo_type *fifoObj, void *newData)
{
    fifoSts_type returnVal = readFail;
    
    unsigned char* newDataAdd = (unsigned char*)newData;
    
    /* If the current data pointer is higher than 0
       it means there has valid data to output */
    if(fifoObj->curPtr > 0)
    {
        /* Output the first item in FIFO */
        memcpyCus(newDataAdd, &fifoObj->fifoData[0], fifoObj->unitLen);
        
        /* Clear the first item content */
        clearDataBlock(&fifoObj->fifoData[0], fifoObj->unitLen);

        /* Move all the existing items to the one position forward */
        memcpyCus(&fifoObj->fifoData[0], &fifoObj->fifoData[1],fifoObj->curPtr - 1);

        /* Move the current pointer of the FIFO */
        fifoObj->curPtr --;

        /* Clear the last valid item content */
        clearDataBlock(&fifoObj->fifoData[fifoObj->curPtr], fifoObj->unitLen);

        returnVal = readSuccess;
    }
    /* If the FIFO is empty then return all zero and
    with the readFail state */
    else{
        clearDataBlock(newDataAdd, fifoObj->unitLen);
        returnVal = readFail;
    }
    return returnVal;
}

fifoSts_type setFifoData(fifo_type *fifoObj, void *newData)
{
    fifoSts_type returnVal = writeFail;

    unsigned char* newDataAdd = (unsigned char*)newData;

    /* Check whether the FIFO has the spare space to write 
       into the new data */
    if((FIFO_MAX_LENGTH - (fifoObj->unitLen * fifoObj->curPtr)) >= fifoObj->unitLen)
    {
        memcpyCus(&fifoObj->fifoData[fifoObj->curPtr], newDataAdd, fifoObj->unitLen);
        fifoObj->curPtr ++;
        returnVal = writeSuccess;
    }
    /* The FIFO is full no space to write then return fail */
    else
    {
        returnVal = readFail;
    }
    return returnVal;
}