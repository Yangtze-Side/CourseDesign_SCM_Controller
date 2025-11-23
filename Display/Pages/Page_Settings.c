/**
 * @file Page_Settings.c
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 页面编写示例。使用时可以在编辑器里将 Example 字样统一替换成自己页面的名字。
 * 
 * @version 0.1
 * @date 2025-07-21
 * 
 */
#include "Page_Settings.h"

#define Page_Settings_State_MAIN            0
#define Page_Settings_State_AR              1
#define Page_Settings_State_GPI             2
#define Page_Settings_State_AFPID           3

static u8 Page_Settings_State = Page_Settings_State_MAIN;
static u8 Page_Settings_Ptr = Page_Settings_State_AR;

void Page_Settings_Subtrate(void)
{
    switch (Page_Settings_State)
    {
        case Page_Settings_State_MAIN:
        {
            OLED_ShowString(1, 1, "Settings");
            OLED_ShowString(2, 1, "1.Angle Reset");
            OLED_ShowString(3, 1, "2.Grav PI");
            OLED_ShowString(4, 1, "3.AF PID");
        } break;
        case Page_Settings_State_AR: Page_Settings_AR_Subtrate(); break;
        case Page_Settings_State_GPI: Page_Settings_GPI_Subtrate(); break;
        case Page_Settings_State_AFPID: Page_Settings_AFPID_Subtrate(); break;
    }
}

void Page_Settings_Task(void)
{
    switch (Page_Settings_State)
    {
        case Page_Settings_State_MAIN:
        {
            OLED_ShowNum(1, 16, Page_Settings_Ptr, 1, FILL_BY_SPACE);
        } break;
        case Page_Settings_State_AR: Page_Settings_AR_Task(); break;
        case Page_Settings_State_GPI: Page_Settings_GPI_Task(); break;
        case Page_Settings_State_AFPID: Page_Settings_AFPID_Task(); break;
    }
}


void Page_Settings_Key_Left(void)
{
    switch (Page_Settings_State)
    {
        case Page_Settings_State_MAIN:
        {
            Page_Settings_Ptr-- == 1 ? Page_Settings_Ptr = Page_Settings_State_AFPID : (void)0;
        } break;
        case Page_Settings_State_AR: Page_Settings_AR_Key_Left(); break;
        case Page_Settings_State_GPI: Page_Settings_GPI_Key_Left(); break;
        case Page_Settings_State_AFPID: Page_Settings_AFPID_Key_Left(); break;
    }
}

void Page_Settings_Key_Right(void)
{
    switch (Page_Settings_State)
    {
        case Page_Settings_State_MAIN:
        {
            ++Page_Settings_Ptr > Page_Settings_State_AFPID ? Page_Settings_Ptr = Page_Settings_State_AR : (void)0;
        } break;
        case Page_Settings_State_AR: Page_Settings_AR_Key_Right(); break;
        case Page_Settings_State_GPI: Page_Settings_GPI_Key_Right(); break;
        case Page_Settings_State_AFPID: Page_Settings_AFPID_Key_Right(); break;
    }
}

void Page_Settings_Key_Mode_ShortPress(void)
{
    switch (Page_Settings_State)
    {
        case Page_Settings_State_MAIN:
        {
            Page_Settings_State = Page_Settings_Ptr;
            OLED_Clear();
            Page_Settings_Subtrate();
        } break;
        case Page_Settings_State_AR: Page_Settings_AR_Key_Mode_ShortPress(); break;
        case Page_Settings_State_GPI: Page_Settings_GPI_Key_Mode_ShortPress(); break;
        case Page_Settings_State_AFPID: Page_Settings_AFPID_Key_Mode_ShortPress(); break;
    }
}

void Page_Settings_Key_Mode_LongPress(void)
{
    switch (Page_Settings_State)
    {
        case Page_Settings_State_MAIN:
        {
            Page_Settings_Ptr = Page_Settings_State_AR;
            ReturnPageMain();
        } break;
        case Page_Settings_State_AR: Page_Settings_AR_Key_Mode_LongPress(); break;
        case Page_Settings_State_GPI: Page_Settings_GPI_Key_Mode_LongPress(); break;
        case Page_Settings_State_AFPID: Page_Settings_AFPID_Key_Mode_LongPress(); break;
    }
}


