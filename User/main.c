#include <REGX52.H>
#include "delay.h"
#include "digital_tube.h"
#include "ds18b20.h"
void main(void)
{
    unsigned char i,ds18b20_status,temperature_data[4] = {0,0,0,0};
	unsigned short temperature_data_math;
	unsigned long count=0;
	ds18b20_status = ds18b20_init();
	for(i = 0;i < 4; i++)
	{
		temperature_data[i] = ds18b20_status?ds18b20_status:16;
	}
    while(1)
    {
        unsigned char i;
		//显示刷新
		if(ds18b20_status && !(count%20))//count控制读取间隔,理论count>30否则会出现无效的数据
		{
			ds18b20_conversion_start();
			ds18b20_read_status();
			temperature_data_math = ds18b20_read_temperature();
			if(temperature_data_math != 0x550 || count>=300)//保证第一次显示的就为有效数据
			{
				//数据处理
				temperature_data[0] = (temperature_data_math&0xf000)?16:17;//符号位显示
				if(temperature_data[0] == 16)//负数
				{
					temperature_data_math = (~temperature_data_math)+1;
				}
				temperature_data[1]=((temperature_data_math>>4)/10)>10?9:((temperature_data_math>>4)/10);//越界处理
				temperature_data[2]=((temperature_data_math>>4)%10)>10?9:((temperature_data_math>>4)%10);//越界处理
#if	0			
				//粗糙处理
				temperature_data[3]=((temperature_data_math&0xf)*10)/16;//小数位处理
#else
				//四舍五入处理
				temperature_data[3]=((temperature_data_math&0xf)*10)%16>8?((temperature_data_math&0xf)*10)/16+1:((temperature_data_math&0xf)*10)/16;//小数位处理
#endif
			}
		}
        for(i = 0; i < 4; i++)//动态显示控制
        {
            move_display_num_CA(temperature_data[i], i ,i==2?1:0);
			delay_ms(10);
        }
		count++;
    }

}