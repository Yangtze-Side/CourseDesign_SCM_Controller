#ifndef __IMU_APP_H
#define __IMU_APP_H

#include "config.h"
#include "MPU6500_SPI.h"
#include "imu_solution_quat.h"

#define MPU6500_SPI_NSS_High()              (P00 = 1)
#define MPU6500_SPI_NSS_Low()               (P00 = 0)

extern EulerAngle_t EulerAngle;

u8   IMU_Init(void);
void IMU_Update(void);

#endif // !__IMU_APP_H
