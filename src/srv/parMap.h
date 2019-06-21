#ifndef __PARMAP_H__
#define __PARMAP_H__

#define PAR_MAP_LENGTH 120

typedef struct{
    unsigned char cmd;
    unsigned char add[2];
    unsigned char opData[2];  
}InterfaceData_type;

extern InterfaceData_type parMap[PAR_MAP_LENGTH];

extern void parMapInit();
extern void parMapRead(unsigned char addH, unsigned char addL, unsigned char *Hdata, unsigned char *Ldata);
extern void parMapWrite(unsigned char addH, unsigned char addL, unsigned char Hdata, unsigned char Ldata);

#endif