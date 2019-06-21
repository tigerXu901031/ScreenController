#ifndef __CRC_H__
#define __CRC_H__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef int int32_t;

extern uint16_t Crc16RtuCal(uint8_t *pDataValue,uint16_t uiDataLen);

#endif