/*****************application.c*************************/

#include "../drv/STC8.H"
#include "../app/ParaDefine.H"
#include "../app/HMI.H" 

#include "intrins.h"
#include "../drv/19296p1.H"
#include "../drv/uartDrv.h"
#include "task.h"

sbit KEY1 		= P1^0;
sbit KEY2 		= P0^7;
sbit KEY_Up 	= P0^6;
sbit KEY_Stop = P0^5;
sbit KEY_Down = P0^4;


extern void AppFunRun(void)
{
	
	
}