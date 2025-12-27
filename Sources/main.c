//<<AICUBE_USER_HEADER_REMARK_BEGIN>>
////////////////////////////////////////
// 在此添加用户文件头说明信息  
// 文件名称: main.c
// 文件描述: 
// 文件版本: V1.0
// 修改记录:
//   1. (2025-11-13) 创建文件
////////////////////////////////////////
//<<AICUBE_USER_HEADER_REMARK_END>>


#include "config.h"                     //默认已包含stdio.h、intrins.h等头文件


//<<AICUBE_USER_INCLUDE_BEGIN>>
// 在此添加用户头文件包含  
#include "task.h"
#include "communication.h"
#include "system.h"
#include "imu_app.h"
#include "Control/control.h"
#include "Joystick.h"
//<<AICUBE_USER_INCLUDE_END>>


//<<AICUBE_USER_GLOBAL_DEFINE_BEGIN>>
// 在此添加用户全局变量定义、用户宏定义以及函数声明  
//<<AICUBE_USER_GLOBAL_DEFINE_END>>



////////////////////////////////////////
// 项目主函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void main(void)
{
    //<<AICUBE_USER_MAIN_INITIAL_BEGIN>>
    // 在此添加用户主函数初始化代码  
    //<<AICUBE_USER_MAIN_INITIAL_END>>

    SYS_Init();

    //<<AICUBE_USER_MAIN_CODE_BEGIN>>
    // 在此添加主函数中运行一次的用户代码  
    // TestLED_ON();
    proj_init();
    //<<AICUBE_USER_MAIN_CODE_END>>

    while (1)
    {
        //<<AICUBE_USER_MAIN_LOOP_BEGIN>>
        // 在此添加主函数中用户主循环代码  
        
        if (GET_TaskExeFlag())
        {
            CLR_TaskExeFlag();
            TaskExe();
        }

        //<<AICUBE_USER_MAIN_LOOP_END>>
    }
}

////////////////////////////////////////
// 系统初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void SYS_Init(void)
{
    EnableAccessXFR();                  //使能访问扩展XFR

    //<<AICUBE_USER_PREINITIAL_CODE_BEGIN>>
    // 在此添加用户预初始化代码  
    //<<AICUBE_USER_PREINITIAL_CODE_END>>

    P0M0 = 0x00; P0M1 = 0x00;           //初始化P0口为准双向口模式
    P1M0 = 0x00; P1M1 = 0x00;           //初始化P1口为准双向口模式
    P2M0 = 0x00; P2M1 = 0x00;           //初始化P2口为准双向口模式
    P3M0 = 0x00; P3M1 = 0x00;           //初始化P3口为准双向口模式
    P4M0 = 0x00; P4M1 = 0x00;           //初始化P4口为准双向口模式
    P5M0 = 0x00; P5M1 = 0x00;           //初始化P5口为准双向口模式
    P6M0 = 0x00; P6M1 = 0x00;           //初始化P6口为准双向口模式
    P7M0 = 0x00; P7M1 = 0x00;           //初始化P7口为准双向口模式

    PORT0_Init();                       //P0口初始化
    PORT1_Init();                       //P1口初始化
    PORT2_Init();                       //P2口初始化
    PORT3_Init();                       //P3口初始化
    PORT4_Init();                       //P4口初始化
    PORT5_Init();                       //P5口初始化
    TIMER0_Init();                      //定时器0初始化
    TIMER1_Init();                      //定时器1初始化
    TIMER2_Init();                      //定时器2初始化
    TIMER3_Init();                      //定时器3初始化
    UART1_Init();                       //串口1初始化
    EXTI0_Init();                       //INT0初始化
    ADC_Init();                         //ADC初始化
    SPI_Init();                         //SPI初始化

    //<<AICUBE_USER_INITIAL_CODE_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_INITIAL_CODE_END>>

    EnableGlobalInt();                  //使能全局中断
}

////////////////////////////////////////
// 微秒延时函数
// 入口参数: us (设置延时的微秒值)
// 函数返回: 无
////////////////////////////////////////
void delay_us(uint16_t us)
{
    do
    {
        NOP(14);                        //(MAIN_Fosc + 500000) / 1000000 - 10
    } while (--us);
}


////////////////////////////////////////
// 毫秒延时函数
// 入口参数: ms (设置延时的毫秒值)
// 函数返回: 无
////////////////////////////////////////
void delay_ms(uint16_t ms)
{
    uint16_t i;

    do
    {
        i = MAIN_Fosc / 10000;
        while (--i);
    } while (--ms);
}


//<<AICUBE_USER_FUNCTION_IMPLEMENT_BEGIN>>
// 在此添加用户函数实现代码   
void led_task(void)
{
    // P13 ^= 1;
    // user_printf("Pitch: %f, Roll: %f, Yaw: %f\r\n", EulerAngle.pitch, EulerAngle.roll, EulerAngle.yaw);
    // user_printf("Vx: %f, Vy: %f, Vw: %f\r\n", ctrl_car.joystick->vx, ctrl_car.joystick->vy, ctrl_car.joystick->vw);
    // user_printf("x: %d, y: %d\r\n", adc_data.adc_ch0, adc_data.adc_ch1);
    // user_printf("F: %f, B: %f, L: %f, R: %f\r\n", US_Data.F, US_Data.B, US_Data.L, US_Data.R);
}

void simulation_led_task(void)
{
#if CODE_SIMULATION
    P13 ^= 1;
#endif
}
//<<AICUBE_USER_FUNCTION_IMPLEMENT_END>>


