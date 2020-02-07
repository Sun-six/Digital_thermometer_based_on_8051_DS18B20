#ifndef	DIGITAL_TUBE_H
#define DIGITAL_TUBE_H
#include <REGX52.H>
//可供显示的字符
#define PEN_CODE_LEN		18
//有几位数码管
#define	DSPLAY_INDEX_LEN	4

//0:共阴	1:共阳
#define DIGITAL_TUBE_TYPE	1
#if DIGITAL_TUBE_TYPE
void move_display_num_CA(unsigned char num, unsigned char index ,unsigned char point_flag);
#else
void move_display_num_CC(unsigned char num, unsigned char index ,unsigned char point_flag);
#endif
#endif