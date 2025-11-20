
#include "key_ud.h"
#include "Display.h"

BOOL Key_UD_Left = Bit_SET, Key_UD_Right = Bit_SET;


static void Key_L_Pressed(void)
{
    switch (ShowState)
    {
        case PAGE_Main: Page_Main_Key_Left(); break;
        case PAGE_Control: Page_Control_Key_Left(); break;

        default: break;
    }
}

static void Key_R_Pressed(void)
{
    switch (ShowState)
    {
        case PAGE_Main: Page_Main_Key_Right(); break;
        case PAGE_Control: Page_Control_Key_Right(); break;

        default: break;
    }
}


/**
 * @brief It is suggest that the function be implemented every 20ms.
 * 
 */
void Key_UD_Task(void)
{
    static bit key_l_last = Bit_SET, key_r_last = Bit_SET;
    Key_UD_Left = Key_UD1_PinIn, Key_UD_Right = Key_UD2_PinIn;

    if (KeyUD_Is_Pressed(key_l_last) && KeyUD_Is_Released(Key_UD_Left))
    {
        Key_L_Pressed();
    }

    if (KeyUD_Is_Pressed(key_r_last) && KeyUD_Is_Released(Key_UD_Right))
    {
        Key_R_Pressed();
    }

    key_l_last = Key_UD_Left, key_r_last = Key_UD_Right;
}
