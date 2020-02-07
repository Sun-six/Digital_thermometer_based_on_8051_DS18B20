#include "ds18b20.h"

#define DS18B20_PIN	P1_0
#define DS18B20_1US		_nop_()
#define DS18B20_2US		DS18B20_1US;DS18B20_1US
#define DS18B20_3US		DS18B20_1US;DS18B20_2US
#define DS18B20_4US		DS18B20_1US;DS18B20_3US
#define DS18B20_5US		DS18B20_1US;DS18B20_4US
#define DS18B20_6US		DS18B20_1US;DS18B20_5US
#define DS18B20_7US		DS18B20_1US;DS18B20_6US
#define DS18B20_8US		DS18B20_1US;DS18B20_7US
#define DS18B20_9US		DS18B20_1US;DS18B20_8US
#define DS18B20_10US	DS18B20_1US;DS18B20_9US
#define DS18B20_50US	DS18B20_10US;DS18B20_10US;DS18B20_10US;DS18B20_10US;DS18B20_10US
#define DS18B20_100US	DS18B20_50US;DS18B20_50US
#define DS18B20_500US	DS18B20_100US;DS18B20_100US;DS18B20_100US;DS18B20_100US;DS18B20_100US
#define DS18B20_1000US	DS18B20_500US;DS18B20_500US
//读取一个字节
unsigned char ds18b20_read_byte(void)
{
    unsigned char i, t_data = 0;

    for(i = 0; i < 8; i++)
    {
        DS18B20_PIN = 0; //产生读时间间隙(读开始)
        DS18B20_2US;
        DS18B20_PIN = 1; //释放总线
        DS18B20_8US;    //等待DS18B20的数据输出
        t_data >>= 1;    //高位补0，默认以0为准

        if(DS18B20_PIN) t_data |= 0x80;

        DS18B20_50US;
        DS18B20_10US;
        DS18B20_PIN = 1; //释放总线,等待读取下一位数据
    }

    return t_data;
}
//写入一个字节
void ds18b20_write_byte(unsigned char cmd)
{
    unsigned char i;

    for(i = 0; i < 8; i++)
    {
        DS18B20_PIN = 0;
        DS18B20_1US;
        DS18B20_PIN = cmd & 0x01; //发送实际的数据位
        DS18B20_50US;
        DS18B20_10US; //等待写完成
        DS18B20_PIN = 1; //释放总线，准备下一次发送
        cmd >>= 1;
    }
}
//模块初始化 1:模块存在 0：模块不存在
unsigned char ds18b20_init(void)
{
    DS18B20_PIN = 1;
    DS18B20_10US;

    if(ds18b20_read_status())
    {
        return 0;
    }

    return 1;
}
//获取状态 1:no 0:ok
unsigned char ds18b20_read_status(void)
{
    unsigned char cnt = 0;
    DS18B20_PIN = 0;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_100US;
    DS18B20_50US;
    DS18B20_PIN = 1;
    DS18B20_10US;
    DS18B20_5US;      //等待DS18B20回应

    while(DS18B20_PIN && cnt < 200)
    {
        cnt++;
    }

    if(cnt >= 200) return 1;

    cnt = 0;

    while(!DS18B20_PIN && cnt < 240)
    {
        cnt++;
    }

    if(cnt >= 240) return 1;

    return 0;
}
//开始转换 0：开启失败	1：开启成功
unsigned char ds18b20_conversion_start(void)
{
    if(ds18b20_read_status())
    {
        return 0;
    }

    ds18b20_write_byte(0xCC); //跳过ROM序列检测
    ds18b20_write_byte(0x44); //启动一次温度转换
    return 1;
}

//读取温度
unsigned short ds18b20_read_temperature(void)
{
    unsigned char temp_H, temp_L, ret;

    ret = ds18b20_init();

    ds18b20_write_byte(0xCC); //跳过ROM序列检测
    ds18b20_write_byte(0x44); //启动一次温度转换

    if(ds18b20_read_status())
    {
        return 0;
    }

    ds18b20_write_byte(0xCC); //跳过ROM序列检测
    ds18b20_write_byte(0xBE); //读取温度
    temp_L = ds18b20_read_byte(); //读取的温度低位数据
    temp_H = ds18b20_read_byte(); //读取的温度高位数据
    return temp_L | (temp_H << 8); //合成温度
}

