
#include "key_ud.h"
#include "Display.h"
#include "system.h"

BOOL Key_L_Now = Bit_SET, Key_R_Now = Bit_SET;


static void Key_L_Pressed(void)
{
    switch (ShowState)
    {
        case PAGE_Main: Page_Main_Key_Left(); break;
        case PAGE_Control: Page_Control_Key_Left(); break;
        case PAGE_Music: Page_Music_Key_Left(); break;
        case PAGE_Settings: Page_Settings_Key_Left(); break;
        case PAGE_About: Page_About_Key_Left(); break;

        default: break;
    }
}

static void Key_R_Pressed(void)
{
    switch (ShowState)
    {
        case PAGE_Main: Page_Main_Key_Right(); break;
        case PAGE_Control: Page_Control_Key_Right(); break;
        case PAGE_Music: Page_Music_Key_Right(); break;
        case PAGE_Settings: Page_Settings_Key_Right(); break;
        case PAGE_About: Page_About_Key_Right(); break;

        default: break;
    }
}

static void Key_LR_Pressed(void)
{
	u8 i = 5;
	OLED_Clear();
	OLED_ShowString(2, 4, "Restarting");
	for (; i <= 12; i++)
	{
		OLED_ShowChar(3, i, '.');
		Sys_Delay(25);
	}
    Software_ResetToISP();
}


/**
 * @brief It is suggest that the function be implemented every 20ms.
 * 
 */
void Key_UD_Task(void)
{
    static bit Key_L_Last = Bit_SET, Key_R_Last = Bit_SET;
    static u8 Key_LR_state = 0, Key_LR_cnt = 0;
    Key_L_Now = Key_UD1_PinIn, Key_R_Now = Key_UD2_PinIn;

    switch (Key_LR_state)
	{
		case 0:
		{
			if (KeyUD_Is_Pressed(Key_L_Now)) Key_LR_state = 1;
			if (KeyUD_Is_Pressed(Key_R_Now)) Key_LR_state = 2;
		} break;

		case 1:
		{
			if (KeyUD_Is_Released(Key_L_Now))	// 如果 L 被松开了
			{
				Key_LR_state = 0;
                Key_L_Pressed();
			}
			else if (KeyUD_Is_Pressed(Key_R_Now))	// 如果 L 还在按着，同时 R 被按下了
			{
				Key_LR_state = 3;
				Key_LR_cnt = 0;
			}
		} break;

		case 2:
		{
			if (KeyUD_Is_Released(Key_R_Now))	// 如果 R 被松开了
			{
				Key_LR_state = 0;
                Key_R_Pressed();
			}
			else if (KeyUD_Is_Pressed(Key_L_Now))	// 如果 R 还在按着，同时 L 被按下了
			{
				Key_LR_state = 3;
				Key_LR_cnt = 0;
			}
		} break;

		case 3:
		{
			if (KeyUD_Is_Released(Key_L_Now) || KeyUD_Is_Released(Key_R_Now))
			{
				// 如果 L、R 至少一个被松开了
				Key_LR_state = 0;		// 算是提前松开的，识别为无效操作
			}
			else
			{
				// 如果俩键还在被按着
				if (++Key_LR_cnt >= 50)
				{
					// 如果到了 1 s
					Key_LR_state = 0;
					Key_LR_Pressed();	// 识别为组合长按
				}
			}
		} break;
	}

    Key_L_Last = Key_L_Now, Key_R_Last = Key_R_Now;
}
