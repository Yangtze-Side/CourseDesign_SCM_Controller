#ifndef __USER_PWM_H
#define __USER_PWM_H

#include "config.h"

#define PWMA_Pin                            P27     // Motor
#define PWMB_Pin                            P45     // Motor
#define PWMC_Pin                            P44     // Motor
// #define PWMD_Pin                            P23     // Motor
// #define PWME_Pin                            LED1     // LED
// #define PWMF_Pin                            LED2     // LED

#define PWM_CLK_DIVIDER                     0      // PWM clock divider (0 ~ 15)
#define PWM_PERIOD                          1000    // PWM period (0 ~ 32767)
#define PWM_PulseWidth_MAX                  PWM_PERIOD

void User_PWM_Init(void);
void User_PWMA_SetWidth(u16 Width);
void User_PWMB_SetWidth(u16 Width);
void User_PWMC_SetWidth(u16 Width);
// void User_PWMD_SetWidth(u16 Width);
// void User_PWME_SetWidth(u16 Width);
// void User_PWMF_SetWidth(u16 Width);

#endif // !__USER_PWM_H
