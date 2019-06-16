#include "isr.h"

void timer1msIsr() interrupt 1
{
    /* Reload countr value and clear interrupt */
	TL0 = 0x40;
	TH0 = 0xA2;
	TF0 = 0;
    TR0 = 1;
    task1ms();

}

void timer10msIsr() interrupt 20
{
    

    T4L = 0xE0;
	T4H = 0xB1;	

    /* set these two bit seems not used in ISR, maybe useful later */	
    // AUXINTIF &= T4IF;
    // T4T3M |= T4R;
    /* Reload countr value and clear interrupt */
    task10ms();
}

void uart3Isr() interrupt 17
{
    uart3Int();
}

void uart4Isr() interrupt 18
{
    uart4Int();
}