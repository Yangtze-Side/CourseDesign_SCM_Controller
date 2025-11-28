#ifndef __IMU_SOLUTION_QUAT_H
#define __IMU_SOLUTION_QUAT_H

#include "config.h"
#include "imu_def.h"


#define halfT_s                 0.010f          // 采样周期

void EulerAngleUpdate_Quat(EulerAngle_t *euler, IMU_Data_t *dat);


#endif // !__IMU_SOLUTION_QUAT_H
