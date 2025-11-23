/**
 * @file PAGE_Settings_AFPID.c
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 页面编写示例。使用时可以在编辑器里将 Example 字样统一替换成自己页面的名字。
 * 
 * @version 0.1
 * @date 2025-07-21
 * 
 */
#include "PAGE_Settings_AFPID.h"
#include "communication.h"


#define Page_Settings_AFPIDKP           0
#define Page_Settings_AFPIDKI           1
#define Page_Settings_AFPIDKD           2

static u8 index = Page_Settings_AFPIDKP;

void Page_Settings_AFPID_Subtrate(void)
{
    OLED_ShowString(1, 1, "AF PID:");
    OLED_ShowString(2, 2, "Kp ");
    OLED_ShowString(3, 2, "Ki ");
    OLED_ShowString(4, 2, "Kd ");

}

void Page_Settings_AFPID_Task(void)
{
    switch (index)
    {
    case Page_Settings_AFPIDKP:
        OLED_ShowString(2, 1, ">");
        OLED_ShowString(3, 1, " ");
        OLED_ShowString(4, 1, " ");
        break;
    case Page_Settings_AFPIDKI:
        OLED_ShowString(2, 1, " ");
        OLED_ShowString(3, 1, ">");
        OLED_ShowString(4, 1, " ");
        break;
    case Page_Settings_AFPIDKD:
        OLED_ShowString(2, 1, " ");
        OLED_ShowString(3, 1, " ");
        OLED_ShowString(4, 1, ">");
        break;
    }

    OLED_ShowNum(2, 5, Comm_PID_Data.afpid_kp, 2, FILL_BY_SPACE);
    OLED_ShowChar(2, 7, '.');
    OLED_ShowNum(2, 8, GetFloatDeci(Comm_PID_Data.afpid_kp, 2), 2, FILL_BY_0);
    OLED_ShowNum(3, 5, Comm_PID_Data.afpid_ki, 2, FILL_BY_SPACE);
    OLED_ShowChar(3, 7, '.');
    OLED_ShowNum(3, 8, GetFloatDeci(Comm_PID_Data.afpid_ki, 3), 3, FILL_BY_0);
    OLED_ShowNum(4, 5, Comm_PID_Data.afpid_kd, 2, FILL_BY_SPACE);
    OLED_ShowChar(4, 7, '.');
    OLED_ShowNum(4, 8, GetFloatDeci(Comm_PID_Data.afpid_kd, 2), 2, FILL_BY_0);
}


void Page_Settings_AFPID_Key_Left(void)
{
    switch (index)
    {
        case Page_Settings_AFPIDKP: Comm_SendRequest(COMM_SendReq_AFPIDkpDec); break;
        case Page_Settings_AFPIDKI: Comm_SendRequest(COMM_SendReq_AFPIDkiDec); break;
        case Page_Settings_AFPIDKD: Comm_SendRequest(COMM_SendReq_AFPIDkdDec); break;
    }
}

void Page_Settings_AFPID_Key_Right(void)
{
    switch (index)
    {
        case Page_Settings_AFPIDKP: Comm_SendRequest(COMM_SendReq_AFPIDkpAdd); break;
        case Page_Settings_AFPIDKI: Comm_SendRequest(COMM_SendReq_AFPIDkiAdd); break;
        case Page_Settings_AFPIDKD: Comm_SendRequest(COMM_SendReq_AFPIDkdAdd); break;
    }
}

void Page_Settings_AFPID_Key_Mode_ShortPress(void)
{
    ++index > Page_Settings_AFPIDKD ? index = Page_Settings_AFPIDKP : (void)0;
}

void Page_Settings_AFPID_Key_Mode_LongPress(void)
{
    index = Page_Settings_AFPIDKP;
    Page_Settings_ReturnToMain();
}
