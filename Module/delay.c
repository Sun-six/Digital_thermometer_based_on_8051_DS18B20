#include "delay.h"

//void delay_us(unsigned long count)
//{
////    unsigned long timer_count;
////    //定时器初值计算
////    timer_count = count;
////	//初始化定时器0
////	TMOD = 0x01;          //使用定时器T0的模式1
////	TF0 = 0;

////	while(timer_count)
////	{
////		unsigned long temp_count = timer_count>65536?65536:timer_count;
////		TH0 = (65536 - temp_count) / 256; //定时器T0的高8位赋初值
////		TL0 = (65536 - temp_count) % 256; //定时器T0的低8位赋初值
////		TR0 = 1;              //启动定时器T0
////		//等待定时器到达
////		while(TF0 == 0);
////		TF0 = 0;
////		timer_count -= temp_count;
////	}
////		#pragma asm
////	RET_DELAY:
////		DJNZ	R7,$;
////		DJNZ	R6,$;
////		DJNZ	R5,$;
////		DJNZ	R4,$;
////		RET
////		#pragma endasm
//}
//延时n毫秒
void delay_ms(unsigned long n)
{
    unsigned long i=0,j=0;
    for(i=0;i<n;i++)
        for(j=0;j<2;j++);
}