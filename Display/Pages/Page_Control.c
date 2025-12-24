/**
 * @file Page_Control.c
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 页面编写示例。使用时可以在编辑器里将 Example 字样统一替换成自己页面的名字。
 * 
 * @version 0.1
 * @date 2025-07-21
 * 
 */
#include "Page_Control.h"
#include "communication.h"
#include "AS5600.h"
#include "Control/control.h"
#include "user_math.h"

#define Page_Control_State_PLAY             0
#define Page_Control_State_SETMODE          1
#define Page_Control_State_SETVW            2

u8 Page_Control_State = Page_Control_State_PLAY;

void Page_Control_Subtrate(void)
{
    OLED_ShowString(2, 16, "%");

    OLED_ShowString(3, 1, "T:");
    OLED_ShowChar(3, 5, '.');
    OLED_ShowString(3, 7, "`C");
    OLED_ShowChar(3, 14, '.');
    OLED_ShowString(3, 10, "H:");
    OLED_ShowString(3, 16, "%");
}

void Page_Control_Task(void)
{
    if (Comm_GetLinkStatus()) OLED_ShowString(1, 1, "OK");
    else OLED_ShowString(1, 1, "DC");

    switch (Control_GetMode())
    {
        case Ctrl_Mode_Gravity:     OLED_ShowString(1, 7, "GR"); break;
        case Ctrl_Mode_JoyStick:    OLED_ShowString(1, 7, "JS"); break;
        case Ctrl_Mode_Encoder:     OLED_ShowString(1, 7, "EN"); break;
        case Ctrl_Mode_AutoCruise:  OLED_ShowString(1, 7, "AC"); break;
        case Ctrl_Mode_AutoFollow:  OLED_ShowString(1, 7, "AF"); break;
    }

    OLED_ShowNum(1, 13, Control_GetVw(), 3, FILL_BY_SPACE);

    OLED_ShowNum(2, 1, (int)encoder_degree, 4, FILL_BY_SPACE);
    OLED_ShowNum(2, 6, (int)Comm_Car_Yaw, 4, FILL_BY_SPACE);
    OLED_ShowNum(2, 13, Comm_GetPackErrPercent(), 3, FILL_BY_SPACE);

    OLED_ShowNum(3, 3,  DHT11_Data.temp_int, 2, FILL_BY_SPACE);
    OLED_ShowNum(3, 6,  DHT11_Data.temp_deci, 1, FILL_BY_SPACE);
    OLED_ShowNum(3, 12, DHT11_Data.humi_int, 2, FILL_BY_SPACE);
    OLED_ShowNum(3, 15, DHT11_Data.humi_deci, 1, FILL_BY_SPACE);

    OLED_ShowNum(4, 1,  (US_Data.F), 3, FILL_BY_0);
    OLED_ShowNum(4, 5,  (US_Data.B), 3, FILL_BY_0);
    OLED_ShowNum(4, 10, (US_Data.L), 3, FILL_BY_0);
    OLED_ShowNum(4, 14, (US_Data.R), 3, FILL_BY_0);

    switch (Page_Control_State)
    {
        case Page_Control_State_PLAY:
        {
            OLED_ShowChar(1, 6, ' ');
            OLED_ShowChar(1, 9, ' ');
            OLED_ShowChar(1, 12, ' ');
            OLED_ShowChar(1, 16, ' ');
        } break;
        
        case Page_Control_State_SETMODE:
        {
            OLED_ShowChar(1, 6, '[');
            OLED_ShowChar(1, 9, ']');
            OLED_ShowChar(1, 12, ' ');
            OLED_ShowChar(1, 16, ' ');
        } break;
        
        case Page_Control_State_SETVW:
        {
            OLED_ShowChar(1, 6, ' ');
            OLED_ShowChar(1, 9, ' ');
            OLED_ShowChar(1, 12, '[');
            OLED_ShowChar(1, 16, ']');
        } break;

        default: break;
    }
}

void Page_Control_Key_Left(void)
{
    switch (Page_Control_State)
    {
        case Page_Control_State_SETMODE:
        {
            Control_ModeDec();
        } break;
        
        case Page_Control_State_SETVW:
        {
            Control_VWDec();
        } break;

        default: break;
    }
}

void Page_Control_Key_Right(void)
{
    switch (Page_Control_State)
    {
        case Page_Control_State_SETMODE:
        {
            Control_ModeInc();
        } break;

        case Page_Control_State_SETVW:
        {
            Control_VWInc();
        } break;

        default: break;
    }
}

void Page_Control_Key_Mode_ShortPress(void)
{
    ++Page_Control_State > Page_Control_State_SETVW ? Page_Control_State = 0 : (void)0;
}

void Page_Control_Key_Mode_LongPress(void)
{
    Page_Control_State = Page_Control_State_PLAY;
    ReturnPageMain();
}
