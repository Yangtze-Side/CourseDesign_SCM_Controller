
#include "FOC_Simulation.h"
#include "FOC_Math.h"
#include "FOC.h"
#include "AS5600.h"


RatchetRegionInfo_t getRatchetRegion(float angle, int n_sections)
{
    RatchetRegionInfo_t info;
    float step;
    float lower;
    float upper;
    float d_lower;
    float d_upper;
    float nearest;
    int region;

    // 1. 归一化角度 0~360
    while (angle < 0) angle += 360.0f;
    while (angle >= 360.0f) angle -= 360.0f;

    // 2. 每个区域宽度
    step = 360.0f / n_sections;

    // 3. 属于第几个区域
    region = (int)(angle / step);

    // 4. 区域上下边界
    lower = region * step;
    upper = lower + step;

    // 5. 判断最近边界
    d_lower = angle - lower;
    d_upper = upper - angle;

    if (d_lower <= d_upper)
        nearest = lower;
    else
        nearest = upper;

    // 写回结构体
    info.region_id    = region;
    info.lower_bound  = lower;
    info.upper_bound  = upper;
    info.nearest_bound = nearest;

    return info;
}

void Ratchet_Simulation_Init(void)
{
    LowPassFilter_Init(&angleControl_loop_filter, 0.8f);
    PosPID_Init(
        &angleControl_loop_pid, 
        0.1f,
        0.1f / 5000.0f,
        0.01f,
        5000.0f, 15.0f,
        2.0f,
        VOLTAGE_POWER_SUPPLY/3
    );
}

void Ratchet_Simulation_Update(s8 direction, u8 notch_number)
{
    RatchetRegionInfo_t r;
    r = getRatchetRegion(encoder_degree, notch_number);
    switch (direction)
    {
        case 0:
            angleControl_loop(r.nearest_bound);     //  顺时针和逆时针均可转动并形成挡位
            break;

        case 1:
            
            break;

        case -1:

            break;
        
        default:
            break;
    }
}
