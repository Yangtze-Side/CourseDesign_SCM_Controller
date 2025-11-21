//<<AICUBE_USER_HEADER_REMARK_BEGIN>>
////////////////////////////////////////
// 在此添加用户文件头说明信息  
// 文件名称: uart.c
// 文件描述: 
// 文件版本: V1.0
// 修改记录:
//   1. (2025-11-14) 创建文件
////////////////////////////////////////
//<<AICUBE_USER_HEADER_REMARK_END>>


#include "config.h"


//<<AICUBE_USER_INCLUDE_BEGIN>>
// 在此添加用户头文件包含  
#include "user_driver.h"
#include "system.h"
//<<AICUBE_USER_INCLUDE_END>>


//<<AICUBE_USER_GLOBAL_DEFINE_BEGIN>>
// 在此添加用户全局变量定义、用户宏定义以及函数声明  
//<<AICUBE_USER_GLOBAL_DEFINE_END>>



////////////////////////////////////////
// 串口1初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void UART1_Init(void)
{
    UART1_SwitchP1617();                //设置串口数据端口: RxD (P1.6), TxD (P1.7)

    UART1_Timer2BRT();                  //选择定时器2作为串口1波特率发生器

    UART1_EnableRx();                   //使能串口1接收数据
    UART1_Mode1();                      //设置串口1为模式1 (8位数据可变波特率)
    UART1_SetIntPriority(1);            //设置中断为高优先级
    UART1_EnableInt();                  //使能串口1中断

    //<<AICUBE_USER_UART1_INITIAL_BEGIN>>
    // 在此添加用户初始化代码  
    //<<AICUBE_USER_UART1_INITIAL_END>>
}


////////////////////////////////////////
// 串口1中断服务程序
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void UART1_ISR(void) interrupt UART1_VECTOR
{
    //<<AICUBE_USER_UART1_ISR_CODE1_BEGIN>>
    // 在此添加中断函数用户代码  
    if (UART1_CheckTxFlag())            //判断串口发送中断
    {
        UART1_ClearTxFlag();            //清除串口发送中断标志
        UART_Send_ITHandler(&uart1_tx);
    }

    if (UART1_CheckRxFlag())            //判断串口接收中断
    {
        UART1_ClearRxFlag();            //清除串口接收中断标志
        UART_Recv_ITHandler(&uart1_rx);
    }
    //<<AICUBE_USER_UART1_ISR_CODE1_END>>
}


//<<AICUBE_USER_FUNCTION_IMPLEMENT_BEGIN>>
// 在此添加用户函数实现代码  
//<<AICUBE_USER_FUNCTION_IMPLEMENT_END>>


