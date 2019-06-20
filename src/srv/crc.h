#ifndef __CRC_H__
#define __CRC_H__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef int int32_t;

extern uint16_t crc16tablefast(uint8_t *ptr, uint16_t len);

#endif