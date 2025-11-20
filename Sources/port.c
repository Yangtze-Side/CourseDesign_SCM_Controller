//<<AICUBE_USER_HEADER_REMARK_BEGIN>>
////////////////////////////////////////
// 在此添加用户文件头说明信息  
// 文件名称: port.c
// 文件描述: 
// 文件版本: V1.0
// 修改记录:
//   1. (2025-11-15) 创建文件
////////////////////////////////////////
//<<AICUBE_USER_HEADER_REMARK_END>>


#include "config.h"


//<<AICUBE_USER_INCLUDE_BEGIN>>
// 在此添加用户头文件包含  
//<<AICUBE_USER_INCLUDE_END>>


//<<AICUBE_USER_GLOBAL_DEFINE_BEGIN>>
// 在此添加用户全局变量定义、用户宏定义以及函数声明  
//<<AICUBE_USER_GLOBAL_DEFINE_END>>



////////////////////////////////////////
// P0口初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void PORT0_Init(void)
{
    SetP0nInitLevelHigh(PIN_ALL);       //设置P0初始化电平
    SetP0nQuasiMode(PIN_ALL);           //设置P0为准双向口模式

    //<<AICUBE_USER_PORT0_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_PORT0_INITIAL_END>>
}

////////////////////////////////////////
// P1口初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void PORT1_Init(void)
{
    SetP1nInitLevelHigh(PIN_ALL);       //设置P1初始化电平
    SetP1nQuasiMode(PIN_6 | PIN_5 | PIN_4 | PIN_3); //设置P1.6,P1.5,P1.4,P1.3为准双向口模式
    SetP1nPushPullMode(PIN_7);          //设置P1.7为推挽输出模式
    SetP1nHighZInputMode(PIN_2 | PIN_1 | PIN_0); //设置P1.2,P1.1,P1.0为高阻输入模式

    //<<AICUBE_USER_PORT1_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_PORT1_INITIAL_END>>
}

////////////////////////////////////////
// P2口初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void PORT2_Init(void)
{
    SetP2nInitLevelHigh(PIN_ALL);       //设置P2初始化电平
    SetP2nQuasiMode(PIN_7 | PIN_6 | PIN_5 | PIN_4 | PIN_0); //设置P2.7,P2.6,P2.5,P2.4,P2.0为准双向口模式
    SetP2nPushPullMode(PIN_3 | PIN_1);  //设置P2.3,P2.1为推挽输出模式
    SetP2nHighZInputMode(PIN_2);        //设置P2.2为高阻输入模式

    //<<AICUBE_USER_PORT2_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_PORT2_INITIAL_END>>
}

////////////////////////////////////////
// P3口初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void PORT3_Init(void)
{
    SetP3nInitLevelHigh(PIN_ALL);       //设置P3初始化电平
    SetP3nQuasiMode(PIN_7 | PIN_6 | PIN_5 | PIN_4 | PIN_3 | PIN_1 | PIN_0); //设置P3.7,P3.6,P3.5,P3.4,P3.3,P3.1,P3.0为准双向口模式
    SetP3nHighZInputMode(PIN_2);        //设置P3.2为高阻输入模式

    //<<AICUBE_USER_PORT3_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_PORT3_INITIAL_END>>
}

////////////////////////////////////////
// P4口初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void PORT4_Init(void)
{
    SetP4nInitLevelHigh(PIN_ALL);       //设置P4初始化电平
    SetP4nQuasiMode(PIN_ALL);           //设置P4为准双向口模式

    //<<AICUBE_USER_PORT4_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_PORT4_INITIAL_END>>
}

////////////////////////////////////////
// P5口初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void PORT5_Init(void)
{
    SetP5nInitLevelHigh(PIN_ALL);       //设置P5初始化电平
    SetP5nQuasiMode(PIN_7 | PIN_6 | PIN_5 | PIN_3 | PIN_2 | PIN_1 | PIN_0); //设置P5.7,P5.6,P5.5,P5.3,P5.2,P5.1,P5.0为准双向口模式
    SetP5nPushPullMode(PIN_4);          //设置P5.4为推挽输出模式

    //<<AICUBE_USER_PORT5_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_PORT5_INITIAL_END>>
}



//<<AICUBE_USER_FUNCTION_IMPLEMENT_BEGIN>>
// 在此添加用户函数实现代码  
//<<AICUBE_USER_FUNCTION_IMPLEMENT_END>>


