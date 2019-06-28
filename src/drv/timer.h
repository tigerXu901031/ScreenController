#ifndef __TIMER_H__
#define __TIMER_H__

#include "STC8.h"

extern void timer25ms_Enable(void);
extern void timer25ms_Disable(void);
extern void timer2ms_Enable(void);
extern void timer2ms_Disable(void);

extern void timerInit();

#endif