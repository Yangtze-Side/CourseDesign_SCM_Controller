/**
 * @file PAGE_Settings_AR_AR.c
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 页面编写示例。使用时可以在编辑器里将 Example 字样统一替换成自己页面的名字。
 * 
 * @version 0.1
 * @date 2025-07-21
 * 
 */
#include "PAGE_Settings_AR.h"
#include "imu_app.h"
#include "Control/control.h"

#define PAGE_Settings_AR_State_Reset_Pitch    0
#define PAGE_Settings_AR_State_Reset_Yaw     1
#define PAGE_Settings_AR_State_Reset_Yaw_Step_One 0
#define PAGE_Settings_AR_State_Reset_Yaw_Step_Two 1


u8 PAGE_Settings_AR_State = 0;
u8 PAGE_Settings_AR_Reset_Yaw_Step = 0;
float First_Yaw_Angle = 0.0f;
float Last_Yaw_Angle = 0.0f;


void Page_Settings_AR_Subtrate(void)
{
    OLED_ShowString(3, 2, "Reset Pitch");
    OLED_ShowString(4, 2, "Reset Yaw");
}

void Page_Settings_AR_Task(void)
{
    OLED_ShowNum(1, 1,  ctrl_car.euler->pitch, 4, FILL_BY_0);
    OLED_ShowNum(1, 6,  ctrl_car.euler->roll,  4, FILL_BY_0);
    OLED_ShowNum(1, 11, ctrl_car.euler->yaw,   4, FILL_BY_0);


    switch (PAGE_Settings_AR_State)
    {
        case PAGE_Settings_AR_State_Reset_Pitch:
            OLED_ShowString(3, 1, ">");
            OLED_ShowString(4, 1, " ");
            OLED_ShowString(4, 12, " ");
            break;

        case PAGE_Settings_AR_State_Reset_Yaw:
            if (PAGE_Settings_AR_Reset_Yaw_Step == PAGE_Settings_AR_State_Reset_Yaw_Step_One) {
                OLED_ShowString(4, 1, ">");
                OLED_ShowString(3, 1, " ");
                OLED_ShowString(4, 12, "1");
            } else if (PAGE_Settings_AR_Reset_Yaw_Step == PAGE_Settings_AR_State_Reset_Yaw_Step_Two) {
                OLED_ShowString(4, 1, ">");
                OLED_ShowString(3, 1, " ");
                OLED_ShowString(4, 12, "2");
            }
            break;

    default:
        break;
    }
}


void Page_Settings_AR_Key_Left(void)
{
    PAGE_Settings_AR_State ^= 1;
}

void Page_Settings_AR_Key_Right(void)
{
    ;
}

void Page_Settings_AR_Key_Mode_ShortPress(void)
{
    switch (PAGE_Settings_AR_State)
    {
        case PAGE_Settings_AR_State_Reset_Pitch:
        {
            Control_CalcPitchBias(EulerAngle.pitch);
        } break;
        case PAGE_Settings_AR_State_Reset_Yaw:
        {
            if (PAGE_Settings_AR_Reset_Yaw_Step == PAGE_Settings_AR_State_Reset_Yaw_Step_One) {
                First_Yaw_Angle = EulerAngle.yaw;
                PAGE_Settings_AR_Reset_Yaw_Step = PAGE_Settings_AR_State_Reset_Yaw_Step_Two;
            } else if (PAGE_Settings_AR_Reset_Yaw_Step == PAGE_Settings_AR_State_Reset_Yaw_Step_Two) {
                Last_Yaw_Angle = EulerAngle.yaw;
                Control_CalcYawBias(First_Yaw_Angle, Last_Yaw_Angle);
                First_Yaw_Angle = 0.0f;
                Last_Yaw_Angle = 0.0f;
                PAGE_Settings_AR_Reset_Yaw_Step = PAGE_Settings_AR_State_Reset_Yaw_Step_One;
            }
        }
        default: break;
    }
}

void Page_Settings_AR_Key_Mode_LongPress(void)
{
    PAGE_Settings_AR_State = PAGE_Settings_AR_State_Reset_Pitch;
    Page_Settings_ReturnToMain();
}
