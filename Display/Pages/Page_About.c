/**
 * @file Page_About.c
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 页面编写示例。使用时可以在编辑器里将 Example 字样统一替换成自己页面的名字。
 * 
 * @version 0.1
 * @date 2025-07-21
 * 
 */
#include "Page_About.h"

static u8 page_about_index = 0;
static u8 page_about_iconIndex = 0;
static char code page_about_icon[4] = { '|', '/', '-', '\\' };


void Page_About_Subtrate(void)
{
    OLED_ShowString(1, 1, "Author:");
    OLED_ShowCnString32(3, 5, "岳子康");
}

void Page_About_Task(void)
{
    OLED_ShowChar(1, 16, page_about_icon[++page_about_iconIndex > 3 ? page_about_iconIndex = 0 : page_about_iconIndex]);

}


void Page_About_Key_Left(void)
{
    ;
}

void Page_About_Key_Right(void)
{
    ;
}

void Page_About_Key_Mode_ShortPress(void)
{
    page_about_index ^= 1;
    switch (page_about_index)
    {
        case 0:
        {
            OLED_ShowCnString32(3, 5, "岳子康");
        } break;

        case 1:
        {
            OLED_ShowCnString32(3, 5, "周玄凌");
        } break;
    }
}

void Page_About_Key_Mode_LongPress(void)
{
	page_about_index = 0;
    ReturnPageMain();
}
