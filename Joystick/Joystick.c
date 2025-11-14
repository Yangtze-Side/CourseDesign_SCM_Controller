
#include "Joystick.h"

ADC_CH_Data adc_data;

void ADC_Task(void)
{
    // 采样通道 0
    adc_data.adc_ch0 = ADC_Convert(0);
    // 采样通道 1
    adc_data.adc_ch1 = ADC_Convert(1);
}

