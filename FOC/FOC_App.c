
#include "FOC_App.h"
#include "FOC.h"
#include "FOC_Simulation.h"
#include "Display.h"
#include "communication.h"
#include "imu_app.h"
#include "AS5600.h"


static u8 last_ShowState = 0;


/****************************************FOC任务执行***************************************************/

// FOC初始化函数
void FOC_Init(void)
{
    Ratchet_Simulation_Init();    // 低通不能给太狠了，微分项要起到消除震荡作用
}


// 这里放FOC控制代码
void FOC_Task(void)
{
    //  切换时重置状态
    if (ShowState != last_ShowState)
    {
        setTorque(0.0f, _3PI_2);
        last_ShowState = ShowState;

        switch (ShowState)
        {
            case PAGE_Main:
            {
                // 给 PID 提供第一组参数
                FOC_SetAnglePID_Param(
                    FOCPID_EFFECT1_Kp,
                    FOCPID_EFFECT1_Ki,
                    FOCPID_EFFECT1_Kd,
                    FOCPID_EFFECT1_IntMax,
                    FOCPID_EFFECT1_IntDis,
                    FOCPID_EFFECT1_DeMax,
                    FOCPID_EFFECT1_UMax
                );
            } break;

            case PAGE_Control:
            {
                // 给 PID 提供第二组参数
                FOC_SetAnglePID_Param(
                    FOCPID_EFFECT2_Kp,
                    FOCPID_EFFECT2_Ki,
                    FOCPID_EFFECT2_Kd,
                    FOCPID_EFFECT2_IntMax,
                    FOCPID_EFFECT2_IntDis,
                    FOCPID_EFFECT2_DeMax,
                    FOCPID_EFFECT2_UMax
                );
            } break;

            case PAGE_About:
            {
                FOC_SetAnglePID_Param(
                    FOCPID_EFFECT2_Kp,
                    FOCPID_EFFECT2_Ki,
                    FOCPID_EFFECT2_Kd,
                    FOCPID_EFFECT2_IntMax,
                    FOCPID_EFFECT2_IntDis,
                    FOCPID_EFFECT2_DeMax,
                    FOCPID_EFFECT2_UMax
                );
            }

            default: break;
        }
    }

    switch (ShowState)
    {
        case PAGE_About:
        {
            if (Do_FOC)
            {
                Do_Swing = 0;
                velocityOpenloop(600);
            }
            else if (Do_Swing)
            {
                Do_FOC = 0;
                // angleControl_loop(EulerAngle.roll);
            }
            else
            {
                setTorque(0.0f, _3PI_2);
            }
        } break;
        
        case PAGE_Control:
        {
            angleControl_loop(Comm_Car_Yaw);
        } break;

        
        case PAGE_Settings:

        case PAGE_Music:

        case PAGE_Main:
        {
            if (Do_Init)
            {
                Zero_Electric_Init();
                Do_Init = 0;
            }
            else
            {
                Ratchet_Simulation_Update(NOTCH_NUM);    // 低通不能给太狠了，微分项要起到消除震荡作用
            }
        } break;

        default:
            break;
    }
}