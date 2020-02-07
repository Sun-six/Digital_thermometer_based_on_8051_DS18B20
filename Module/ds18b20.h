#ifndef DS18B20_H
#define DS18B20_H
#include <REGX52.H>
#include "delay.h"
//读取温度
unsigned short ds18b20_read_temperature(void);
//开始转换 0：开启失败	1：开启成功
unsigned char ds18b20_conversion_start(void);
//获取状态 1:no 0:ok
unsigned char ds18b20_read_status(void);
//模块初始化 1:模块存在 0：模块不存在
unsigned char ds18b20_init(void);
#endif