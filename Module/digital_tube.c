#include "digital_tube.h"

#ifdef DIGITAL_TUBE_TYPE
//0~F的显示码，最后两位为-&空白
const unsigned char code Display_Pen_Code_CA[PEN_CODE_LEN]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 
							0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 
							0xa1, 0x86, 0x8e,0xbf,0xff};
void move_display_num_CA(unsigned char num, unsigned char index ,unsigned char point_flag)
{
    if(num >= PEN_CODE_LEN || index >= DSPLAY_INDEX_LEN)
    {
        return ;
    }
	//先进行位选，再进行段选，增加显示稳定性
    P2 = 0x1 << index;
    P0 = point_flag?Display_Pen_Code_CA[num]&0x7f:Display_Pen_Code_CA[num];
}
#else
//0~F的显示码，最后两位为-&空白
const unsigned char code Display_Pen_Code_CC[PEN_CODE_LEN]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 
							0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 
							0x5e, 0x79, 0x71,0x40,0x00};
void move_display_num_CC(unsigned char num, unsigned char index ,unsigned char point_flag)
{
    if(num >= PEN_CODE_LEN || index >= DSPLAY_INDEX_LEN)
    {
        return ;
    }
	//先进行位选，再进行段选，增加显示稳定性
    P2 = ~(0x1 << index);
    P0 = point_flag?Display_Pen_Code_CC[num]|0x80:Display_Pen_Code_CC[num];
}
#endif




