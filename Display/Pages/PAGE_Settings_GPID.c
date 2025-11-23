/**
 * @file PAGE_Settings_GPI.c
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 页面编写示例。使用时可以在编辑器里将 Example 字样统一替换成自己页面的名字。
 * 
 * @version 0.1
 * @date 2025-07-21
 * 
 */
#include "PAGE_Settings_GPID.h"
#include "communication.h"
#include "user_lib.h"

#define Page_Settings_GPIDKP           0
#define Page_Settings_GPIDKI           1
#define Page_Settings_GPIDKD           2

static u8 index = Page_Settings_GPIDKP;

void Page_Settings_GPID_Subtrate(void)
{
    OLED_ShowString(1, 1, "Grav PID:");
    OLED_ShowString(2, 2, "Kp ");
    OLED_ShowString(3, 2, "Ki ");
    OLED_ShowString(4, 2, "Kd ");

}

void Page_Settings_GPID_Task(void)
{
    switch (index)
    {
    case Page_Settings_GPIDKP:
        OLED_ShowString(2, 1, ">");
        OLED_ShowString(3, 1, " ");
        OLED_ShowString(4, 1, " ");
        break;
    case Page_Settings_GPIDKI:
        OLED_ShowString(2, 1, " ");
        OLED_ShowString(3, 1, ">");
        OLED_ShowString(4, 1, " ");
        break;
    case Page_Settings_GPIDKD:
        OLED_ShowString(2, 1, " ");
        OLED_ShowString(3, 1, " ");
        OLED_ShowString(4, 1, ">");
        break;
    }

    OLED_ShowNum(2, 5, Comm_PID_Data.gpid_kp, 2, FILL_BY_SPACE);
    OLED_ShowChar(2, 7, '.');
    OLED_ShowNum(2, 8, GetFloatDeci(Comm_PID_Data.gpid_kp, 2), 2, FILL_BY_0);
    OLED_ShowNum(3, 5, Comm_PID_Data.gpid_ki, 2, FILL_BY_SPACE);
    OLED_ShowChar(3, 7, '.');
    OLED_ShowNum(3, 8, GetFloatDeci(Comm_PID_Data.gpid_ki, 3), 3, FILL_BY_0);
    OLED_ShowNum(4, 5, Comm_PID_Data.gpid_kd, 2, FILL_BY_SPACE);
    OLED_ShowChar(4, 7, '.');
    OLED_ShowNum(4, 8, GetFloatDeci(Comm_PID_Data.gpid_kd, 2), 2, FILL_BY_0);
}


void Page_Settings_GPID_Key_Left(void)
{
    switch (index)
    {
        case Page_Settings_GPIDKP: Comm_SendRequest(COMM_SendReq_GPIDkpDec); break;
        case Page_Settings_GPIDKI: Comm_SendRequest(COMM_SendReq_GPIDkiDec); break;
        case Page_Settings_GPIDKD: Comm_SendRequest(COMM_SendReq_GPIDkdDec); break;
    }
}

void Page_Settings_GPID_Key_Right(void)
{
    switch (index)
    {
        case Page_Settings_GPIDKP: Comm_SendRequest(COMM_SendReq_GPIDkpAdd); break;
        case Page_Settings_GPIDKI: Comm_SendRequest(COMM_SendReq_GPIDkiAdd); break;
        case Page_Settings_GPIDKD: Comm_SendRequest(COMM_SendReq_GPIDkdAdd); break;
    }
}

void Page_Settings_GPID_Key_Mode_ShortPress(void)
{
    ++index > Page_Settings_GPIDKD ? index = Page_Settings_GPIDKP : (void)0;
}

void Page_Settings_GPID_Key_Mode_LongPress(void)
{
    index = Page_Settings_GPIDKP;
    Page_Settings_ReturnToMain();
}
