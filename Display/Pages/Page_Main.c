/**
 * @file Page_Main.c
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 主页面的显示和按键功能。
 * 
 * @version 0.1
 * @date 2025-07-15
 * 
 */
#include "Page_Main.h"
#include "communication.h"


// 主页面中的功能选择指针。0 - 当前显示封面。
// >0 : 表示指向 ShowState 中的具体功能。每一个功能都对应一个页面。
u8 Page_Main_Ptr = 0;


/*---------------------------------------------- User Determine -------------------------------------------*/

/**
 * @brief 主页面显示的衬底
 * 
 */
void Page_Main_Subtrate(void)
{
    switch (Page_Main_Ptr)
    {
        case 0:
        {
            OLED_ShowCnString16(1, 1, "欢迎");
            OLED_ShowChar(1, 5, '!');
            OLED_ShowString(2, 1, "--------");
        } break;
        
        case 1:
        case 2:
        case 3:
        case 4:
        {
            OLED_ShowString(1, 1, "1."); OLED_ShowCnString16(1, 3, "纵横决荡");
            OLED_ShowString(2, 1, "2."); OLED_ShowCnString16(2, 3, "鼓瑟吹萧");
            OLED_ShowString(3, 1, "3."); OLED_ShowCnString16(3, 3, "约法三章");
            OLED_ShowString(4, 1, "4."); OLED_ShowCnString16(4, 3, "问所从来");
        } break;
    }
}


/**
 * @brief 主页面刷新的信息
 * 
 */
void Page_Main_Task(void)
{
    if (Page_Main_Ptr == 0)
    {
        if (Comm_GetLinkStatus())
        {
            OLED_ShowCnString16(4, 1, "连上了");
            OLED_ShowChar(4, 7, ',');
            OLED_ShowCnString16(4, 8, "玩去吧");
        }
        else
        {
            OLED_ShowCnString16(4, 1, "蓝牙未连接");
            OLED_ShowString(4, 11, "   ");
        }
    }
    else
    {
        OLED_ShowNum(1, 16, Page_Main_Ptr, 1, FILL_BY_SPACE);
    }
}


void Page_Main_Key_Left(void)
{
    if (Page_Main_Ptr-- == 0)
    {
        Page_Main_Ptr = PageMain_Ptr_MAX;
    }
    Display_Subtrate();
}

void Page_Main_Key_Right(void)
{
    if (++Page_Main_Ptr > PageMain_Ptr_MAX)
    {
        Page_Main_Ptr = 0;
    }
    Display_Subtrate();
}


void Page_Main_Key_Mode_ShortPress(void)
{
    if (Page_Main_Ptr > 0)
    {
        ShowState = (Page_enum)Page_Main_Ptr;
        Display_Subtrate();
    }
}

void Page_Main_Key_Mode_LongPress(void)
{
    Page_Main_Ptr = 0;
    OLED_Clear();
    Page_Main_Subtrate();
}
