//<<AICUBE_USER_HEADER_REMARK_BEGIN>>
////////////////////////////////////////
// 在此添加用户文件头说明信息  
// 文件名称: config.h
////////////////////////////////////////
//<<AICUBE_USER_HEADER_REMARK_END>>


#ifndef __CONFIG_H__
#define __CONFIG_H__


//<<AICUBE_USER_DEFINE_BEGIN>>
// 在此添加用户宏定义  
#define USE_MPU6500             1
//<<AICUBE_USER_DEFINE_END>>


#define __ENCODING              "UTF-8" //DO NOT DELETE or MODIFY


#define FOSC                    24000000UL
#define SYSCLK                  FOSC
#define MAIN_Fosc               FOSC

#include <stc15.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <intrins.h>

#include "def.h"
#include "stc15w_def.h"


//<<AICUBE_USER_INCLUDE_BEGIN>>
// 在此添加用户头文件包含  
#include "user_def.h"
//<<AICUBE_USER_INCLUDE_END>>


#define KEY_MODE                P06
#define OLED_SCL                P54
#define OLED_SDA                P55
#define ENC_SCL                 P33
#define ENC_SDA                 P34
#define PWM_C                   P44
#define NSS_PIN                 P24
#define PWM_A                   P27
#define PWM_B                   P45
#define KEY_LEFT                P00
#define KEY_RIGHY               P03


#include "port.h"
#include "timer.h"
#include "uart.h"
#include "exti.h"
#include "adc.h"
#include "spi.h"

void SYS_Init(void);
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);



//<<AICUBE_USER_EXTERNAL_DECLARE_BEGIN>>
// 在此添加用户外部函数和外部变量声明  
//<<AICUBE_USER_EXTERNAL_DECLARE_END>>


#endif
