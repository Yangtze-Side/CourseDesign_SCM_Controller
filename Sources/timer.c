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
//<<AICUBE_USER_INCLUDE_END>>


//<<AICUBE_USER_GLOBAL_DEFINE_BEGIN>>
// 在此添加用户全局变量定义、用户宏定义以及函数声明  
//<<AICUBE_USER_GLOBAL_DEFINE_END>>



////////////////////////////////////////
// 定时器0初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void TIMER0_Init(void)
{
#define T0_RELOAD               (65536 - (float)SYSCLK / 12 * 1 / 1000)

    TIMER0_TimerMode();                 //设置定时器0为定时模式
    TIMER0_12TMode();                   //设置定时器0为12T模式
    TIMER0_Mode0();                     //设置定时器0为模式0 (16位自动重载模式)
    TIMER0_DisableGateINT0();           //禁止定时器0门控
    TIMER0_SetIntPriority(0);           //设置中断为低优先级
    TIMER0_EnableInt();                 //使能定时器0中断
    TIMER0_SetReload16(T0_RELOAD);      //设置定时器0的16位重载值
    TIMER0_Run();                       //定时器0开始运行

    //<<AICUBE_USER_TIMER0_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_TIMER0_INITIAL_END>>
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
// 定时器0中断服务程序
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void TIMER0_ISR(void) interrupt TMR0_VECTOR
{
    //<<AICUBE_USER_TIMER0_ISR_CODE1_BEGIN>>
    // 在此添加中断函数用户代码  
    
    static u8 t0_cnt = 0;
    static u8 foc_cnt = 0;
    if (++t0_cnt >= 5)
    {
        t0_cnt = 0;
        // 5ms TODO
        SET_TaskExeFlag();
        // IMU_Update();
        // Control_UpdateEuler();
        SecCnt_Task();
    }
    if (++foc_cnt >= 2)
    {
        FOC_Task();
        foc_cnt = 0;
    }
    
    // 1ms TODO
    Sys_IncTick();
    //<<AICUBE_USER_TIMER0_ISR_CODE1_END>>
}


//<<AICUBE_USER_FUNCTION_IMPLEMENT_BEGIN>>
// 在此添加用户函数实现代码  
//<<AICUBE_USER_FUNCTION_IMPLEMENT_END>>


