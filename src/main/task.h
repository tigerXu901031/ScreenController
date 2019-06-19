#ifndef __TASK_H__
#define __TASK_H__

#include "../app/ParaDefine.H"
#include "../app/HMI.H" 
#include "../app/application.H"
#include "../drv/timer.h"
#include "../drv/STC8.H"
#include "../drv/19296p1.H"
#include "../srv/uartNetwork.h"
// #include "intrins.h"
/* test purpose only */
#include "../drv/uartDrv.h"

extern void taskInit();
extern void task1ms();
extern void task10ms();

/*  */
extern void IO_INIT();
extern void INIT_LCD();
extern void clear_screen();
extern void delay_ms(unsigned int time);

extern SystemStatusType SysStatus;

#endif