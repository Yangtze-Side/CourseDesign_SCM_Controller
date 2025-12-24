#ifndef __FOC_SIMULATION_H
#define __FOC_SIMULATION_H

#include "config.h"
#include "FOC_Util.h"

#define FOCPID_EFFECT1_Kp       0.03f
#define FOCPID_EFFECT1_Ki       0.40f / FOCPID_EFFECT1_IntMax   // Ki 和 Kd 的幅值差不多
#define FOCPID_EFFECT1_Kd       0.45f / FOCPID_EFFECT1_DeMax
#define FOCPID_EFFECT1_IntMax   48.0f       // 虽然 intDis 给的大，但是 intMax 不能太大，否则靠近目标点时会积得特别慢
#define FOCPID_EFFECT1_IntDis   15.0f       // 因为 Kp 给小了，所以积分失能可以给大一点，这样可以弥补 P 项的不足
#define FOCPID_EFFECT1_DeMax    1.6f
#define FOCPID_EFFECT1_UMax     VOLTAGE_POWER_SUPPLY/2

#define FOCPID_EFFECT2_Kp       0.03f
#define FOCPID_EFFECT2_Ki       0.35f / FOCPID_EFFECT2_IntMax
#define FOCPID_EFFECT2_Kd       0.40f / FOCPID_EFFECT2_DeMax
#define FOCPID_EFFECT2_IntMax   48.0f
#define FOCPID_EFFECT2_IntDis   15.0f
#define FOCPID_EFFECT2_DeMax    1.6f
#define FOCPID_EFFECT2_UMax     VOLTAGE_POWER_SUPPLY/3


typedef struct {
    int region_id;        // 落在哪个区域
    float lower_bound;    // 区域下边界
    float upper_bound;    // 区域上边界
    float nearest_bound;  // 最近的边界
} RatchetRegionInfo_t;


void Ratchet_Simulation_Init(void);
void Ratchet_Simulation_Update(u8 notch_number);

#endif