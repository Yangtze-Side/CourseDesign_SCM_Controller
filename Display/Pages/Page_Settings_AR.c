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


u8 PAGE_Settings_AR_State = 0;


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
            break;

        case PAGE_Settings_AR_State_Reset_Yaw:
            OLED_ShowString(4, 1, ">");
            OLED_ShowString(3, 1, " ");
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
    PAGE_Settings_AR_State ^= 1;
}

void Page_Settings_AR_Key_Mode_ShortPress(void)
{
    switch (PAGE_Settings_AR_State)
    {
        case PAGE_Settings_AR_State_Reset_Pitch:
        {
            Control_CalcPitchBias();
        } break;
        case PAGE_Settings_AR_State_Reset_Yaw:
        {
            Control_CalcYawBias();
        } break;
        default: break;
    }
}

void Page_Settings_AR_Key_Mode_LongPress(void)
{
    PAGE_Settings_AR_State = PAGE_Settings_AR_State_Reset_Pitch;
    Page_Settings_ReturnToMain();
}
