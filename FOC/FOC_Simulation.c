
#include "FOC_Simulation.h"
#include "FOC_Math.h"
#include "FOC.h"
#include "AS5600.h"


void getRatchetRegion(float angle, int n_sections, RatchetRegionInfo_t *info)
{
    float step;
    float lower;
    float upper;
    float d_lower;
    float d_upper;
    float nearest;
    int region;

    // 1. 归一化角度 0~360
    while (angle < 0.0f) angle += 360.0f;
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
    info->region_id    = region;
    info->upper_bound  = upper;
    info->lower_bound  = lower;
    info->nearest_bound = nearest;
}

void Ratchet_Simulation_Init(void)
{
    LowPassFilter_Init(&angleControl_loop_filter, 0.4f);
    PosPID_Init(
        &angleControl_loop_pid,
        FOCPID_EFFECT1_Kp,
        FOCPID_EFFECT1_Ki,
        FOCPID_EFFECT1_Kd,
        FOCPID_EFFECT1_IntMax,
        FOCPID_EFFECT1_IntDis,
        FOCPID_EFFECT1_DeMax,
        FOCPID_EFFECT1_UMax
    );
}

void Ratchet_Simulation_Update(u8 notch_number)
{
    RatchetRegionInfo_t r;
    getRatchetRegion(encoder_degree, notch_number, &r);
    angleControl_loop(r.nearest_bound);     //  顺时针和逆时针均可转动并形成挡位
}
