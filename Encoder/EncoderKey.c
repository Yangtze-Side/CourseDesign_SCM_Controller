#include "EncoderKey.h"
#include "AS5600.h"
#include "user_math.h"
#include "Display.h"
#include "FOC_Simulation.h"
#include "FOC_App.h"

s8 last_region;
static float accum = 0;


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

s8 getEncoderRegion(float angle, u8 n_sections)
{
    float step = 360.0f / n_sections;
    float shifted;
    s8 region;

    // 将角度归一化到 (-180, 180]
    angle = Lim_Ang_180(angle);

    // 区间中心在：0, step, 2*step, ...
    // 所以将 angle 右移 step/2 使得 [-step/2, +step/2] 属于区间 0
    shifted = angle + step / 2.0f;

    // 再次规范化 (-180~180]
    shifted = Lim_Ang_180(shifted);

    // 计算区间 idx
    region = (s8)(shifted / step);

    // 修复 C 语言负数除法向零取整导致的问题
    if (shifted < 0.0f)
        region -= 1;

    // 限制范围
    if (region < 0)
        region += n_sections;
    if (region >= n_sections)
        region -= n_sections;

    return region;
}

void EncoderKey_Init(void)
{
    last_region = getEncoderRegion(encoder_degree, NOTCH_NUM);
}

void EncoderKey_Update(void)
{
    s8 now_region = getEncoderRegion(encoder_degree, NOTCH_NUM);
    if ((ShowState != PAGE_Control)&&(ShowState != PAGE_About))
    {
        // 顺时针跨越上边界
        if (((last_region < now_region)&&((last_region - now_region) == -1)) || (last_region - now_region) == 5)
        {
            Key_L_Pressed();
            last_region = now_region;
        }
        // 逆时针跨越下边界
        else if (((last_region > now_region)&&((last_region - now_region) == 1)) || (last_region - now_region) == -5)
        {
            Key_R_Pressed();
            last_region = now_region;
        }
    }
}
