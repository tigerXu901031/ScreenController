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

void clearDataBlock(unsigned int *startAdd, unsigned int length)
{
    unsigned int i = 0;
    for(i = 0; i < length; i ++)
    {
        *startAdd = 0x00;
        *startAdd ++;
    }
}

fifo_type fifoInit(unsigned int unitLen)
{
    fifo_type fifoObj;
    fifoObj.unitLen = unitLen;
    fifoObj.curPtr = 0;

    return fifoObj;
}

fifoSts_type getFifoData(fifo_type *fifoObj, void *newData)
{
    fifoSts_type returnVal = readFail;
    
    newData = (unsigned int)newData;
    
    /* If the current data pointer is higher than 0
       it means there has valid data to output */
    if(fifoObj->curPtr > 0)
    {
        /* Output the first item in FIFO */
        memcpy(newData, &fifoObj->fifoData[0], fifoObj->unitLen);
        
        /* Clear the first item content */
        clearDataBlock(&fifoObj->fifoData[0], fifoObj->unitLen);

        /* Move all the existing items to the one position forward */
        memcpy(&fifoObj->fifoData[0], &fifoObj->fifoData[1],fifoObj->curPtr - 1);

        /* Clear the last valid item content */
        clearDataBlock(&fifoObj->fifoData[fifoObj->curPtr], fifoObj->unitLen);

        /* Move the current pointer of the FIFO */
        fifoObj->curPtr --;

        returnVal = readSuccess;
    }
    /* If the FIFO is empty then return all zero and
    with the readFail state */
    else{
        clearDataBlock(newData, fifoObj->unitLen);
        returnVal = readFail;
    }
    return returnVal;
}

fifoSts_type setFifoData(fifo_type *fifoObj, void *newData)
{
    fifoSts_type returnVal = writeFail;

    newData = (unsigned int)newData;

    /* Check whether the FIFO has the spare space to write 
       into the new data */
    if((FIFO_MAX_LENGTH - (fifoObj->unitLen * fifoObj->curPtr)) >= fifoObj->unitLen)
    {
        memcpy(&fifoObj->fifoData[fifoObj->curPtr], newData, fifoObj->unitLen);
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