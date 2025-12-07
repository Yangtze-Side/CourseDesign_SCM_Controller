
#include "FOC_App.h"
#include "FOC.h"
#include "FOC_Simulation.h"
#include "Page_Main.h"



/****************************************FOC任务执行***************************************************/

// FOC初始化函数
void FOC_Init(void)
{
    // PosPID_Init(
    //     &angleControl_loop_pid, 
    //     0.2f,
    //     2.0f / 5000.0f,
    //     0.01,
    //     5000.0f, 15.0f,
    //     2.0f,
    //     VOLTAGE_POWER_SUPPLY/2
    // );
	// LowPassFilter_Init(&angleControl_loop_filter, 0.1f);
	// PosPI_Init(&velocityControl_loop_pid, 0.0025f, 6.0f / 50000.0f, 50000.0f, 300.0f, VOLTAGE_POWER_SUPPLY/2);
	// LowPassFilter_Init(&velocityControl_loop_filter, 1.0f);

    Ratchet_Simulation_Init();    // 低通不能给太狠了，微分项要起到消除震荡作用
    // Damp_Simulation_Init();
}


// 这里放FOC控制代码
void FOC_Task(void)
{
	// Set_PWM_Frequency(&htim1, 1000);
	// velocityOpenloop(600.0f);  // 速度开环测试，10度每秒 
	// angleControl_loop(45.0f);  // 位置闭环测试，目标位置45度
	// setTorque(VOLTAGE_POWER_SUPPLY / 2, _3PI_2);
	// velocityControl_loop(1000.0f);
    if (Do_Init)
    {
        Zero_Electric_Init();
        Do_Init = 0;
    }
    else
    {
        Ratchet_Simulation_Update(NOTCH_NUM);    // 低通不能给太狠了，微分项要起到消除震荡作用
    }
    // Damp_Simulation_Update(-1);
}