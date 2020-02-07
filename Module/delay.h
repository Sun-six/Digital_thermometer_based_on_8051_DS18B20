#ifndef	TIMER_DELAY_H
#define TIMER_DELAY_H
#include <REGX52.H>
#include <intrins.h>

//定时器0主频
#define TIMER_0_IN_FREQ	12
//定时器1主频
#define TIMER_1_IN_FREQ	12

//void delay_us(unsigned long count);
void delay_ms(unsigned long count);

#endif