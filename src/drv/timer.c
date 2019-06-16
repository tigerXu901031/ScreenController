#include "timer.h"

static void timer4Init(void)
{
    /* 10ms @ 24Mhz */
	T4T3M &= 0x0F;		// Fosc / 12T, timer output disable
	T4L = 0xE0;			// set initial lower byte value for timer
	T4H = 0xB1;			// set initial higher byte value for timer 
}

static void timer0Init(void)
{
    /* 1ms @ 24Mhz */
	AUXR |= 0x80;	// 定时器时钟1T模式
	TMOD &= 0xF0;	// 设置定时器模式
	TL0 = 0x40;		// 设置定时初值
	TH0 = 0xA2;		// 设置定时初值
	TF0 = 0;		// 清除TF0标志
	TR0 = 1;		// 定时器0开始计时
    ET0 = 1;        // enable interupt
}

void timer10ms_Enable(void)
{
	T4T3M |= 0x80;		/* timer 4 start counting */ 
	IE2 |= ET4;            /*  */ 
}

void timer10ms_Disable(void)
{
	T4T3M &= 0x7F;		/* timer 4 stop counting */ 
	IE2 &= ~ET4;
}

void timer1ms_Enable(void)
{
	T4T3M |= 0x80;		/* timer 0 start counting */ 
	IE2 |= ET4;            /*  */ 
}

void timer1ms_Disable(void)
{
	T4T3M &= 0x7F;		/* timer 0 stop counting */ 
	IE2 &= ~ET4;
}

void timerInit()
{
    timer4Init();
    timer0Init();
}