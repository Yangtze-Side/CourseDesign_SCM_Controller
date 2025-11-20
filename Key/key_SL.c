/**
 * @file key.c
 * @author Zach (2063408575@qq.com)
 * 
 * @brief 按键模板，区分长短按。适用单个按键的情况。
 * 
 *        一些细节，如按键电平极性和长短按阈值等，在 .c 文件开头的宏定义处设置。
 * 
 * @version 0.1
 * @date 2025-07-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "key_SL.h"
#include "Display.h"

/*------------------------------------------- User Determine -------------------------------------------*/

#define GET_KEY_NOW()               (P06)     // 当前按键的值

#define Key_IsPressed(__key__)      ((__key__) == Bit_RESET)
#define Key_IsReleased(__key__)     ((__key__) == Bit_SET)

#define Key_TaskPeriod              (20)    // KeyTask 20 ms 执行一次
#define Key_LP_THRES                (600 / Key_TaskPeriod)      // 长按阈值


static void Key_ShortPress(void)
{
    switch (ShowState)
    {
        case PAGE_Main: Page_Main_Key_Mode_ShortPress(); break;
        case PAGE_Control: Page_Control_Key_Mode_ShortPress(); break;

        default: break;
    }
}


static void Key_LongPress(void)
{
    switch (ShowState)
    {
        case PAGE_Main: Page_Main_Key_Mode_LongPress(); break;
        case PAGE_Control: Page_Control_Key_Mode_LongPress(); break;

        default: break;
    }
}


/*---------------------------------------------- Library ----------------------------------------------*/

/**
 * @brief 按键周期性任务，20 ms 执行一次。
 * @note  区分长按、短按。
 * 
 */
void KeySL_Task(void)
{
    static bit keyLast = Bit_RESET;
    static u8 keyState = 0, keyCount = 0;
    bit keyNow = GET_KEY_NOW();

    switch (keyState)
    {
        case 0:
        {
            if (Key_IsPressed(keyNow) && Key_IsReleased(keyLast))
            {
                keyState = 1;
                keyCount = 0;
            }
        } break;

        case 1:
        {
            if (Key_IsPressed(keyNow))
            {
                if (++keyCount >= Key_LP_THRES)
                {
                    keyState = 0;
                    Key_LongPress();
                }
            }
            else
            {
                keyState = 0;
                Key_ShortPress();
            }
        } break;
    }

    keyLast = keyNow;
}
