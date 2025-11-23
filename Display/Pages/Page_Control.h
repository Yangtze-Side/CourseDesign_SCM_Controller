/**
 * @file Page_Control.h
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 页面编写示例。使用时可以在编辑器里将 Example 字样统一替换成自己页面的名字。
 * 
 * @version 0.1
 * @date 2025-07-21
 * 
 */
#ifndef __PAGE_Control_H
#define __PAGE_Control_H

#include "Display.h"

#define Page_Control_State_PLAY             0
#define Page_Control_State_SETMODE          1
#define Page_Control_State_SETVW            2

extern u8 Page_Control_State;

void Page_Control_Subtrate(void);
void Page_Control_Task(void);

void Page_Control_Key_Left(void);
void Page_Control_Key_Right(void);
void Page_Control_Key_Mode_ShortPress(void);
void Page_Control_Key_Mode_LongPress(void);

#endif // !__PAGE_Control_H
