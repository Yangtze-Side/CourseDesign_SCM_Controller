
#include "user_pwm.h"

/**
 * @brief Initialize PWM periperal. Determined by user.
 * 
 */
void User_PWM_Init(void)
{
    PWM_Disable();

    PWM_CLK_SYSCLK();
    PWM_SetClockDivider(PWM_CLK_DIVIDER);       //设置系统时钟的分频值 [SYSCLK/(n+1)]
    PWM_SetCounter(PWM_PERIOD);                 //使能PWM周期值

    PWM_C2_SwitchP27();                 //设置PWM2端口: PWM2 (P2.7)
    PWM_InitialC2Low();                 //设置PWM2通道初始电平为低电平
    PWM_SetC2T1Point(0);                //使能PWM2翻转点1的计数值
    PWM_SetC2T2Point(1);                //使能PWM2翻转点2的计数值
    PWM_DisableC2Output();              //不使能PWM2通道输出

    PWM_C3_SwitchP21();                 //设置PWM3端口: PWM3 (P2.1)
    PWM_InitialC3Low();                 //设置PWM3通道初始电平为低电平
    PWM_SetC3T1Point(0);                //使能PWM3翻转点1的计数值
    PWM_SetC3T2Point(1);                //使能PWM3翻转点2的计数值
    PWM_DisableC3Output();              //不使能PWM3通道输出

    PWM_C4_SwitchP22();                 //设置PWM4端口: PWM4 (P2.2)
    PWM_InitialC4Low();                 //设置PWM4通道初始电平为低电平
    PWM_SetC4T1Point(0);                //使能PWM4翻转点1的计数值
    PWM_SetC4T2Point(1);                //使能PWM4翻转点2的计数值
    PWM_DisableC4Output();              //不使能PWM4通道输出

    // PWM_C5_SwitchP23();                 //设置PWM5端口: PWM5 (P2.3)
    // PWM_InitialC5Low();                 //设置PWM5通道初始电平为低电平
    // PWM_SetC5T1Point(0);                //使能PWM5翻转点1的计数值
    // PWM_SetC5T2Point(1);                //使能PWM5翻转点2的计数值
    // PWM_DisableC5Output();              //不使能PWM5通道输出

    // PWM_C6_SwitchP07();                 //设置PWM6端口: PWM6 (P0.7)
    // PWM_InitialC6Low();                 //设置PWM6通道初始电平为低电平
    // PWM_SetC6T1Point(0);                //使能PWM6翻转点1的计数值
    // PWM_SetC6T2Point(1);                //使能PWM6翻转点2的计数值
    // PWM_DisableC6Output();              //不使能PWM6通道输出

    // PWM_C7_SwitchP17();                 //设置PWM7端口: PWM7 (P1.7)
    // PWM_InitialC7Low();                 //设置PWM7通道初始电平为低电平
    // PWM_SetC7T1Point(0);                //使能PWM7翻转点1的计数值
    // PWM_SetC7T2Point(1);                //使能PWM7翻转点2的计数值
    // PWM_DisableC7Output();              //不使能PWM7通道输出

    PWMA_Pin = 0;
    PWMB_Pin = 0;
    PWMC_Pin = 0;
    // PWMD_Pin = 0;
    // PWME_Pin = 0;
    // PWMF_Pin = 0;

    PWM_Enable();
}

/**
 * @brief Set PWMA pulse width.
 * 
 * @param Width Pulse width. (0 ~ PWM_PulseWidth_MAX)
 */
void User_PWMA_SetWidth(u16 Width)
{
    if (Width >= PWM_PulseWidth_MAX)
    {
        PWM_DisableC2Output();
        PWMA_Pin = 1;
    }
    else if (Width == 0)
    {
        PWM_DisableC2Output();
        PWMA_Pin = 0;
    }
    else
    {
        PWM_SetC2T2Point(Width);
        PWM_EnableC2Output();
    }
}

/**
 * @brief Set PWMB pulse width.
 * 
 * @param Width Pulse width. (0 ~ PWM_PulseWidth_MAX)
 */
void User_PWMB_SetWidth(u16 Width)
{
    if (Width >= PWM_PulseWidth_MAX)
    {
        PWM_DisableC3Output();
        PWMB_Pin = 1;
    }
    else if (Width == 0)
    {
        PWM_DisableC3Output();
        PWMB_Pin = 0;
    }
    else
    {
        PWM_SetC3T2Point(Width);
        PWM_EnableC3Output();
    }
}

/**
 * @brief Set PWMC pulse width.
 * 
 * @param Width Pulse width. (0 ~ PWM_PulseWidth_MAX)
 */
void User_PWMC_SetWidth(u16 Width)
{
    if (Width >= PWM_PulseWidth_MAX)
    {
        PWM_DisableC4Output();
        PWMC_Pin = 1;
    }
    else if (Width == 0)
    {
        PWM_DisableC4Output();
        PWMC_Pin = 0;
    }
    else
    {
        PWM_SetC4T2Point(Width);
        PWM_EnableC4Output();
    }
}

// /**
//  * @brief Set PWMD pulse width.
//  * 
//  * @param Width Pulse width. (0 ~ PWM_PulseWidth_MAX)
//  */
// void User_PWMD_SetWidth(u16 Width)
// {
//     if (Width >= PWM_PulseWidth_MAX)
//     {
//         PWM_DisableC5Output();
//         PWMD_Pin = 1;
//     }
//     else if (Width == 0)
//     {
//         PWM_DisableC5Output();
//         PWMD_Pin = 0;
//     }
//     else
//     {
//         PWM_SetC5T2Point(Width);
//         PWM_EnableC5Output();
//     }
// }

// /**
//  * @brief Set PWME pulse width.
//  * 
//  * @param Width Pulse width. (0 ~ PWM_PulseWidth_MAX)
//  */
// void User_PWME_SetWidth(u16 Width)
// {
//     if (Width >= PWM_PulseWidth_MAX)
//     {
//         PWM_DisableC6Output();
//         PWME_Pin = 1;
//     }
//     else if (Width == 0)
//     {
//         PWM_DisableC6Output();
//         PWME_Pin = 0;
//     }
//     else
//     {
//         PWM_SetC6T2Point(Width);
//         PWM_EnableC6Output();
//     }
// }

// /**
//  * @brief Set PWMF pulse width.
//  * 
//  * @param Width Pulse width. (0 ~ PWM_PulseWidth_MAX)
//  */
// void User_PWMF_SetWidth(u16 Width)
// {
//     if (Width >= PWM_PulseWidth_MAX)
//     {
//         PWM_DisableC7Output();
//         PWMF_Pin = 1;
//     }
//     else if (Width == 0)
//     {
//         PWM_DisableC7Output();
//         PWMF_Pin = 0;
//     }
//     else
//     {
//         PWM_SetC7T2Point(Width);
//         PWM_EnableC7Output();
//     }
// }
