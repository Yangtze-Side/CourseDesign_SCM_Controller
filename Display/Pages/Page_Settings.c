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
#include "imu_app.h"
#include "control.h"


#define Page_Settings_State_Reset_Pitch    0
#define Page_Settings_State_Reset_Yaw     1
#define Page_Settings_State_Reset_Yaw_Step_One 0
#define Page_Settings_State_Reset_Yaw_Step_Two 1

u8 Page_Settings_State = 0;
u8 Page_Settings_Reset_Yaw_Step = 0;
float First_Yaw_Angle = 0.0f;
float Last_Yaw_Angle = 0.0f;


void Page_Settings_Subtrate(void)
{
    OLED_ShowString(2, 2, "Reset Pitch");
    OLED_ShowString(3, 2, "Reset Yaw");
}

void Page_Settings_Task(void)
{
    OLED_ShowNum(1, 1, EulerAngle.pitch, 3, FILL_BY_0);
    OLED_ShowNum(1, 5, EulerAngle.roll,  3, FILL_BY_0);
    OLED_ShowNum(1, 9, EulerAngle.yaw, 3, FILL_BY_0);


    switch (Page_Settings_State)
    {
        case Page_Settings_State_Reset_Pitch:
            OLED_ShowString(2, 1, ">");
            OLED_ShowString(3, 1, " ");
            OLED_ShowString(3, 12, " ");
            break;

        case Page_Settings_State_Reset_Yaw:
            if (Page_Settings_Reset_Yaw_Step == Page_Settings_State_Reset_Yaw_Step_One) {
                OLED_ShowString(3, 1, ">");
                OLED_ShowString(2, 1, " ");
                OLED_ShowString(3, 12, "1");
            } else if (Page_Settings_Reset_Yaw_Step == Page_Settings_State_Reset_Yaw_Step_Two) {
                OLED_ShowString(3, 1, ">");
                OLED_ShowString(2, 1, " ");
                OLED_ShowString(3, 12, "2");
            }
            break;

    default:
        break;
    }
}


void Page_Settings_Key_Left(void)
{
    Page_Settings_State ^= 1;
}

void Page_Settings_Key_Right(void)
{
    ;
}

void Page_Settings_Key_Mode_ShortPress(void)
{
    switch (Page_Settings_State)
    {
        case Page_Settings_State_Reset_Pitch:
        {
            Control_CalcPitchBias(EulerAngle.pitch);
        } break;
        case Page_Settings_State_Reset_Yaw:
        {
            if (Page_Settings_Reset_Yaw_Step == Page_Settings_State_Reset_Yaw_Step_One) {
                First_Yaw_Angle = EulerAngle.yaw;
                Page_Settings_Reset_Yaw_Step = Page_Settings_State_Reset_Yaw_Step_Two;
            } else if (Page_Settings_Reset_Yaw_Step == Page_Settings_State_Reset_Yaw_Step_Two) {
                Last_Yaw_Angle = EulerAngle.yaw;
                Control_CalcYawBias(First_Yaw_Angle, Last_Yaw_Angle);
                First_Yaw_Angle = 0.0f;
                Last_Yaw_Angle = 0.0f;
                Page_Settings_Reset_Yaw_Step = Page_Settings_State_Reset_Yaw_Step_One;
            }
        }
        default: break;
    }
}

void Page_Settings_Key_Mode_LongPress(void)
{
    Page_Settings_State = Page_Settings_State_Reset_Pitch;
    ReturnPageMain();
}
