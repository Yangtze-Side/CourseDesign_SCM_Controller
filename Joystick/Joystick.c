
#include "Joystick.h"

ADC_CH_Data_t adc_data = { 0 };

void ADC_Task(void)
{
    // 采样 x 轴的电压
    adc_data.adc_ch0 = ADC_Convert(ADC_CHANNEL_X);
    // 采样 y 轴的电压
    adc_data.adc_ch1 = ADC_Convert(ADC_CHANNEL_Y);
}
