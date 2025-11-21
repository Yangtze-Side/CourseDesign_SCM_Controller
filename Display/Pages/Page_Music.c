/**
 * @file Page_Music.c
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief 页面编写示例。使用时可以在编辑器里将 Example 字样统一替换成自己页面的名字。
 * 
 * @version 0.1
 * @date 2025-07-21
 * 
 */
#include "Page_Music.h"
#include "communication.h"

#define MUSIC_MIN               1
#define MUSIC_MAX               4

static u8 music_index = 1;
static BOOL music_num_setting = 0;
static u8 music_ptr = 0;

void Page_Music_Subtrate(void)
{
    OLED_ShowString(1, 1, "Music");
    OLED_ShowString(2, 1, ">Play: ");
    OLED_ShowString(3, 1, " Pause");
    OLED_ShowString(4, 1, " Stop");
}

void Page_Music_Task(void)
{
    OLED_ShowNum(2, 9, music_index, 2, FILL_BY_0);

    switch (music_ptr)
    {
        case 0:
        {
            OLED_ShowChar(2, 1, '>');
            OLED_ShowChar(3, 1, ' ');
            OLED_ShowChar(4, 1, ' ');
        } break;
        
        case 1:
        {
            OLED_ShowChar(3, 1, '>');
            OLED_ShowChar(2, 1, ' ');
            OLED_ShowChar(4, 1, ' ');
        } break;
        
        case 2:
        {
            OLED_ShowChar(4, 1, '>');
            OLED_ShowChar(3, 1, ' ');
            OLED_ShowChar(2, 1, ' ');
        } break;
    }

    if (music_num_setting)
    {
        OLED_ShowChar(2, 8, '[');
        OLED_ShowChar(2, 11, ']');
    }
    else
    {
        OLED_ShowChar(2, 8, ' ');
        OLED_ShowChar(2, 11, ' ');
    }
}


void Page_Music_Key_Left(void)
{
    if (music_num_setting) music_index-- == 0 ? music_index = MUSIC_MAX : (void)0;
    else music_ptr == 0 ? music_ptr = 2 : music_ptr--;
}


void Page_Music_Key_Right(void)
{
    if (music_num_setting) ++music_index > MUSIC_MAX ? music_index = MUSIC_MIN: (void)0;
    else ++music_ptr > 2 ? music_ptr = 0 : (void)0;
}


void Page_Music_Key_Mode_ShortPress(void)
{
    switch (music_ptr)
    {
        case 0:
        {
            if (music_num_setting) Comm_MusicStart(music_index);
            music_num_setting ^= 1;
        } break;

        case 1: Comm_MusicPause(); break;
        case 2: Comm_MusicStop(); break;
    }
}

void Page_Music_Key_Mode_LongPress(void)
{
    ReturnPageMain();
}
