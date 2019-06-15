#ifndef __TIMER_H__
#define __TIMER_H__

#include "STC8.h"

extern void timer10ms_Enable(void);
extern void timer10ms_Disable(void);
extern void timer1ms_Enable(void);
extern void timer1ms_Disable(void);

extern void timerInit();

#endif