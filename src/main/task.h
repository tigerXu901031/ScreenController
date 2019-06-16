#ifndef __TASK_H__
#define __TASK_H__

#include "../drv/timer.h"
#include "../drv/uartDrv.h"
#include "../srv/uartNetwork.h"

extern void taskInit();
extern void task1ms();
extern void task10ms();

/*  */
extern void IO_INIT();
extern void INIT_LCD();
extern void clear_screen();
extern void delay_ms(unsigned int time);

#endif