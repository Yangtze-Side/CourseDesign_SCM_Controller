//<<AICUBE_USER_HEADER_REMARK_BEGIN>>
////////////////////////////////////////
// 在此添加用户文件头说明信息  
// 文件名称: timer.c
// 文件描述: 
// 文件版本: V1.0
// 修改记录:
//   1. (2025-11-14) 创建文件
////////////////////////////////////////
//<<AICUBE_USER_HEADER_REMARK_END>>


#include "config.h"


//<<AICUBE_USER_INCLUDE_BEGIN>>
// 在此添加用户头文件包含  
#include "task.h"
#include "system.h"
#include "imu_app.h"
#include "control.h"
#include "FOC_App.h"
#include "AS5600.h"

//<<AICUBE_USER_INCLUDE_END>>


//<<AICUBE_USER_GLOBAL_DEFINE_BEGIN>>
// 在此添加用户全局变量定义、用户宏定义以及函数声明  
// u8 imuUpdateTime_ms = 0;
//<<AICUBE_USER_GLOBAL_DEFINE_END>>



////////////////////////////////////////
// 定时器0初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void TIMER0_Init(void)
{
#define T0_RELOAD               (65536 - (float)SYSCLK / 12 * 1 / 1000) //定时周期1毫秒

    TIMER0_TimerMode();                 //设置定时器0为定时模式
    TIMER0_12TMode();                   //设置定时器0为12T模式
    TIMER0_Mode0();                     //设置定时器0为模式0 (16位自动重载模式)
    TIMER0_DisableGateINT0();           //禁止定时器0门控
    TIMER0_SetIntPriority(1);           //设置中断为高优先级
    TIMER0_EnableInt();                 //使能定时器0中断
    TIMER0_SetReload16(T0_RELOAD);      //设置定时器0的16位重载值
    TIMER0_Run();                       //定时器0开始运行

    //<<AICUBE_USER_TIMER0_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_TIMER0_INITIAL_END>>
}

////////////////////////////////////////
// 定时器1初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void TIMER1_Init(void)
{
#define T1_RELOAD               (65536 - (float)SYSCLK / 12 * 5 / 1000) //定时周期5毫秒

    TIMER1_TimerMode();                 //设置定时器1为定时模式
    TIMER1_12TMode();                   //设置定时器1为12T模式
    TIMER1_Mode0();                     //设置定时器1为模式0 (16位自动重载模式)
    TIMER1_DisableGateINT1();           //禁止定时器1门控
    TIMER1_SetIntPriority(0);           //设置中断为低优先级
    TIMER1_EnableInt();                 //使能定时器1中断
    TIMER1_SetReload16(T1_RELOAD);      //设置定时器1的16位重载值
    TIMER1_Run();                       //定时器1开始运行

    //<<AICUBE_USER_TIMER1_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_TIMER1_INITIAL_END>>
}

////////////////////////////////////////
// 定时器2初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void TIMER2_Init(void)
{
#ifdef BAUDRATE
#undef BAUDRATE
#endif
#define BAUDRATE                (115200)
#define T2_RELOAD               (65536 - (SYSCLK / BAUDRATE + 2) / 4)

    TIMER2_TimerMode();                 //设置定时器2为定时模式
    TIMER2_1TMode();                    //设置定时器2为1T模式
    TIMER2_SetReload16(T2_RELOAD);      //设置定时器2的16位重载值
    TIMER2_Run();                       //定时器2开始运行

    //<<AICUBE_USER_TIMER2_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_TIMER2_INITIAL_END>>
}

////////////////////////////////////////
// 定时器3初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void TIMER3_Init(void)
{
#define T3_RELOAD               (65536 - (float)SYSCLK / 12 * 10 / 1000) //定时周期10毫秒

    TIMER3_TimerMode();                 //设置定时器3为定时模式
    TIMER3_12TMode();                   //设置定时器3为12T模式
    TIMER3_EnableInt();                 //使能定时器3中断
    TIMER3_SetReload16(T3_RELOAD);      //设置定时器3的16位重载值
    TIMER3_Run();                       //定时器3开始运行

    //<<AICUBE_USER_TIMER3_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_TIMER3_INITIAL_END>>
}


////////////////////////////////////////
// 定时器0中断服务程序
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void TIMER0_ISR(void) interrupt TMR0_VECTOR
{
    //<<AICUBE_USER_TIMER0_ISR_CODE1_BEGIN>>
    // 在此添加中断函数用户代码  
    
    static u8 t0_cnt = 0;

    // 1ms TODO
    Sys_IncTick();

    if (++t0_cnt >= 5)
    {
        t0_cnt = 0;
        // 5ms TODO
        SET_TaskExeFlag();
        // IMU_Update();
        // Control_UpdateEuler();
        SecCnt_Task();
    }

    //<<AICUBE_USER_TIMER0_ISR_CODE1_END>>
}

////////////////////////////////////////
// 定时器1中断服务程序
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void TIMER1_ISR(void) interrupt TMR1_VECTOR
{
    //<<AICUBE_USER_TIMER1_ISR_CODE1_BEGIN>>
    // 在此添加中断函数用户代码  
    // 5ms TODO
    AS5600_Update();
    FOC_Task();
    //<<AICUBE_USER_TIMER1_ISR_CODE1_END>>
}

////////////////////////////////////////
// 定时器3中断服务程序
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void TIMER3_ISR(void) interrupt TMR3_VECTOR
{
    //<<AICUBE_USER_TIMER3_ISR_CODE1_BEGIN>>
    // 在此添加中断函数用户代码  
    // u32 tickStart = Sys_GetTick();
    // 注：这个函数的执行时间为 3 ~ 5 ms（24 MHz）
    // 但是在中断里每 5 或 6 ms 执行一次会导致程序卡顿
    // 原因不明
    // 然后就改成每 10 ms 执行一次就好了
    IMU_Update();
    // imuUpdateTime_ms = (u8)(Sys_GetTick() - tickStart);
    //<<AICUBE_USER_TIMER3_ISR_CODE1_END>>
}


//<<AICUBE_USER_FUNCTION_IMPLEMENT_BEGIN>>
// 在此添加用户函数实现代码  
//<<AICUBE_USER_FUNCTION_IMPLEMENT_END>>


