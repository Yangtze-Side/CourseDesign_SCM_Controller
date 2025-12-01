#include "EncoderKey.h"
#include "AS5600.h"
#include "user_math.h"
#include "Display.h"

u16 last_angle;
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

void EncoderKey_Init(void)
{
    last_angle = (u16)encoder_degree - 180;
}

void EncoderKey_Update(void)
{
    float speed;
    float accel = 1.0;
    
    // 读取当前角度
    u16 current_angle = (u16)encoder_degree - 180;
    int16_t diff = Lim_Ang_180((int16_t)(current_angle - last_angle));
    last_angle = current_angle;

    // 拒绝抖动
    if (ABS(diff) < 5) return;

    // 计算转速
    speed = (float)(ABS(diff)) / TASK_CYCLE_MS;

    // 多段加速度
    if (speed > SPEED_STEP_ONE)      accel = ACC_ONE;
    if (speed > SPEED_STEP_TWO)      accel = ACC_TWO;
    if (speed > SPEED_STEP_THREE)    accel = ACC_THREE;

    // 累积
    accum += (int)(diff * accel);

    while (accum >= STEP_THRESHOLD) {
        Key_L_Pressed();
        accum -= STEP_THRESHOLD;
    }

    while (accum <= -STEP_THRESHOLD) {
        Key_R_Pressed();
        accum += STEP_THRESHOLD;
    }
}
