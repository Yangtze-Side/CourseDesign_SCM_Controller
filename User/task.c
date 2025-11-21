
#include "task.h"
#include "imu_app.h"
#include "system.h"
#include "communication.h"
#include "Joystick.h"
#include "Display.h"
#include "key_ud.h"
#include "key_SL.h"
#include "Control/control.h"

void led_task(void);

volatile BOOL TaskExeFlag = 0;

typedef struct
{
    const u16 period;
    u16 count;
    void (*taskHook)(void);
} Task_t;

#define TASK_TOTAL      6

Task_t Task[TASK_TOTAL] =
{
    // { 5/5, 0, IMU_Update },
    { 50/5, 0, ADC_Task },

    { 20/5, 0, Key_UD_Task },
    { 20/5, 0, KeySL_Task },
    { 5/5, 0, sys_uart_recv_task_5ms },
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
        // IMU_Update();
        ADC_Task();
        sys_uart_recv_task_5ms();
        Comm_SendTask();
        led_task();
        Display_Task();
        Key_UD_Task();
        KeySL_Task();
        // Control_Update();
    }
}
