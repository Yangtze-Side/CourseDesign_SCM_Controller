#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "config.h"

// 你需要设计一个任务，利用你编写的 ADC 驱动，及时地更新两路 ADC 采集得来的电压数据，
// 并把结果存放在一个结构体中。这个结果暂时不需要转换成速度数据，因为你可以在 control.c
// 中转换它，这里只是编写底层转换过程。你可以每 50 ms 执行一次这个任务。

#define ADC_CHANNEL_X           1
#define ADC_CHANNEL_Y           0

// ADC 数据在 0 ~ 1024 之间
#define ADC_MAX                 1024
#define ADC_MIN                 0
#define ADC_ZERO                512     // ADC 零点

/**
    摇杆数据如下:
            0
            |
    1024 ---|--- 0
            |
           1024
*/

typedef struct {
    uint16_t adc_ch0;   // ADC 通道 0 的原始采样值
    uint16_t adc_ch1;   // ADC 通道 1 的原始采样值
} ADC_CH_Data_t;

extern ADC_CH_Data_t adc_data;

void ADC_Task(void);

#endif // !__JOYSTICK_H
