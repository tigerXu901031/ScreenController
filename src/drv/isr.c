#include "isr.h"

void timer2msIsr() interrupt 1
{
    /* Reload countr value and clear interrupt */
	TL0 = 0x80;
	TH0 = 0x44;
	TF0 = 0;
    TR0 = 1;
    task2ms();

}

void timer25msIsr() interrupt 20
{
    
    // P44 = 1;

    T4L = 0xB0;
	T4H = 0x3C;	

    /* set these two bit seems not used in ISR, maybe useful later */	
    // AUXINTIF &= T4IF;
    // T4T3M |= T4R;
    /* Reload countr value and clear interrupt */
    task25ms();
    // P44 = 0;

}

void uart3Isr() interrupt 17 using 1
{
    uart3Int();
}

void uart4Isr() interrupt 18
{
    uart4Int();
}