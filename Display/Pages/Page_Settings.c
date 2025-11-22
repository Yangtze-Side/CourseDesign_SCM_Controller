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


void Page_Settings_Subtrate(void)
{
    OLED_ShowString(1, 1, "Pitch");
    OLED_ShowString(2, 1, "Roll");
    OLED_ShowString(3, 1, "Yaw");
}

void Page_Settings_Task(void)
{
    OLED_ShowNum(1, 6, EulerAngle.pitch, 4, FILL_BY_0);
    OLED_ShowNum(2, 6, EulerAngle.roll,  4, FILL_BY_0);
    OLED_ShowNum(3, 6, EulerAngle.yaw, 4, FILL_BY_0);
}


void Page_Settings_Key_Left(void)
{
    ;
}

void Page_Settings_Key_Right(void)
{
    ;
}

void Page_Settings_Key_Mode_ShortPress(void)
{
    ;
}

void Page_Settings_Key_Mode_LongPress(void)
{
    ReturnPageMain();
}
