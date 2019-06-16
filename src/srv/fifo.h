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
    unsigned char fifoData[FIFO_MAX_LENGTH];
    unsigned char unitLen;
    unsigned char curPtr;
}fifo_type;

extern void clearDataBlock(unsigned char *startAdd, unsigned char length);
extern void memcpyCus(unsigned char *destAdd,unsigned char *sourceAdd, unsigned char length);
extern fifo_type fifoInit(unsigned char unitLen);
extern fifoSts_type getFifoData(fifo_type *fifoObj, void *newData);
extern fifoSts_type setFifoData(fifo_type *fifoObj, void *newData);

#endif