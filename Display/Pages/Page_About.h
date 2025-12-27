/**
 * @file Page_About.h
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 页面编写示例。使用时可以在编辑器里将 Example 字样统一替换成自己页面的名字。
 * 
 * @version 0.1
 * @date 2025-07-21
 * 
 */
#ifndef __PAGE_About_H
#define __PAGE_About_H

#include "Display.h"

extern BOOL Do_FOC;
extern BOOL Do_Swing;

void Page_About_Subtrate(void);
void Page_About_Task(void);

void Page_About_Key_Left(void);
void Page_About_Key_Right(void);
void Page_About_Key_Mode_ShortPress(void);
void Page_About_Key_Mode_LongPress(void);

#endif // !__PAGE_About_H
