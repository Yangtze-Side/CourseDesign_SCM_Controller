
#include "task.h"
#include "imu_app.h"
#include "system.h"

void led_task(void);

volatile BOOL TaskExeFlag = 0;

typedef struct
{
    const u16 period;
    u16 count;
    void (*taskHook)(void);
} Task_t;

#define TASK_TOTAL      3

Task_t Task[TASK_TOTAL] =
{
    { 5/5, 0, IMU_Update },
    { 5/5, 0, sys_uart_recv_task_5ms },
    { 500/5, 0, led_task },
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
}
