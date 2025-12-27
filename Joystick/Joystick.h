#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "config.h"


#define ADC_CHANNEL_X           1
#define ADC_CHANNEL_Y           0

// ADC 数据在 0 ~ 1023 之间
#define ADC_MAX                 1023
#define ADC_MIN                 0
#define ADC_ZERO                511     // ADC 零点

/**
    摇杆数据如下:
            0
            |
    1023 ---|--- 0
            |
           1023
*/

typedef struct {
    uint16_t adc_ch0;   // ADC 通道 0 的原始采样值
    uint16_t adc_ch1;   // ADC 通道 1 的原始采样值
} ADC_CH_Data_t;

extern ADC_CH_Data_t adc_data;

void ADC_Task(void);

#endif // !__JOYSTICK_H
