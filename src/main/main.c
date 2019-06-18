#include "../drv/STC8.H"
//#include "../app/ParaDefine.H"
//#include "../app/HMI.H" 

#include "intrins.h"
//#include "../drv/19296p1.H"
#include "../drv/uartDrv.h"
#include "task.h"

#define  time_ms 400 

//sbit LED1 = P3^6;
//sbit LED2 = P3^5;
//sbit Key1 = P3^2;
//sbit Key2 = P3^3;

//uchar count=0;

//���ܣ���ʱ�ӳ���  ������time  Ϊ����ms��
void delay_ms(unsigned int time)
{
	 unsigned int  i;
	 unsigned int  j;
	 for(i=0;i<time;i++)
		for(j=0;j<1668;j++);
}

//���ܣ�IO��ʼ��  ��������
void IO_INIT()
{
	;
}

void main()
{

//	Timer10ms_Disable();
	taskInit();
	
	while(1)											//��ѭ��
	{;}
}
