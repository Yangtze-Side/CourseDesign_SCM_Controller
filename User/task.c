
#include "task.h"
#include "imu_app.h"
#include "system.h"
#include "communication.h"
#include "Joystick.h"
#include "Display.h"
#include "key_ud.h"
#include "key_SL.h"
#include "AS5600.h"
#include "EncoderKey.h"
#include "Control/control.h"

void led_task(void);

volatile BOOL TaskExeFlag = 0;
volatile u32 time_now = 0;

void time_task(void)        //  5ms
{
    time_now++;
    if(time_now >= UINT32_MAX - 1)
    {
        time_now = 0;
    }
}

typedef struct
{
    const u16 period;
    u16 count;
    void (*taskHook)(void);
} Task_t;

#define TASK_TOTAL      9

Task_t Task[TASK_TOTAL] =
{
    { 5/5, 0, time_task},
    { 10/5, 0, IMU_Update },
    { 10/5, 0, AS5600_Update },
    { 50/5, 0, ADC_Task },
    { 20/5, 0, Key_UD_Task },
    { 20/5, 0, KeySL_Task },
    { 20/5, 0, EncoderKey_Update },
    
    { 60/5, 0, Comm_SendTask },

    { 100/5, 0, Display_Task },
    // { 500/5, 0, led_task },
};

void TaskExe(void)
{
    u8 i = 0;
    for (; i < TASK_TOTAL; i++)
    {
        if (++Task[i].count >= Task[i].period)
        {
            Task[i].count = 0;
            if (Task[i].taskHook != NULL)
            {
                Task[i].taskHook();
            }
        }
    }

    // Pretend to call the task functions
    if (i > TASK_TOTAL)
    {
        time_task();
        IMU_Update();
        ADC_Task();
        Comm_SendTask();
        led_task();
        Display_Task();
        Key_UD_Task();
        KeySL_Task();
        EncoderKey_Update();
        AS5600_Update();
        // Control_Update();
    }
}
