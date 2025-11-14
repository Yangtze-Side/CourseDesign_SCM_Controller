#ifndef __USER_ADC_H
#define __USER_ADC_H

#include "config.h"

// 你需要查阅 STC15-DS.pdf，编写阻塞性触发 ADC 通道转换并读取转换结果的驱动函数。
// 函数以 User_ADC_ 开头。
// 可以先试试配置 AICube，看看会生成怎样的初始化代码，ADC 的转换函数也可能在 adc.h 里给出。
// 如果没有给出，那你需要自己编写，相关的宏可以参考 stc15w_def.h 文件，搜索 ADC 可以看到一些辅助宏函数。

#endif // !__USER_ADC_H
