#ifndef __FIFO_H__
#define __FIFO_H__

/* Maximum length of FIFO 100 Byte */
#define FIFO_MAX_LENGTH 100

typedef enum{
    readSuccess     = 0x11,
    readFail        = 0x33,
    writeSuccess    = 0x22,
    writeFail       = 0xAA,
}fifoSts_type;

typedef struct{
    unsigned int fifoData[FIFO_MAX_LENGTH];
    unsigned int unitLen;
    unsigned int curPtr;
}fifo_type;

extern void clearDataBlock(unsigned int *startAdd, unsigned int length);
extern void memcpy(unsigned int *destAdd,unsigned int *sourceAdd, unsigned int length);
extern fifo_type fifoInit(unsigned int unitLen);
extern fifoSts_type getFifoData(fifo_type *fifoObj, void *newData);
extern fifoSts_type setFifoData(fifo_type *fifoObj, void *newData);

#endif