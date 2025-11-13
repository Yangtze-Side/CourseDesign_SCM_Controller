#ifndef __USER_PWM_H
#define __USER_PWM_H

#include "config.h"

#define PWMA_Pin                            P27
#define PWMB_Pin                            P21
#define PWMC_Pin                            P22
#define PWMD_Pin                            P23

#define PWM_CLK_DIVIDER                     12          // PWM clock divider (0 ~ 15)
#define PWM_PERIOD                          2000        // PWM period (0 ~ 32767)

void User_PWM_Init(void);
void User_PWMA_SetWidth(u16 Width);
void User_PWMB_SetWidth(u16 Width);
void User_PWMC_SetWidth(u16 Width);
void User_PWMD_SetWidth(u16 Width);

#endif // !__USER_PWM_H
