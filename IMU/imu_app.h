#ifndef __IMU_APP_H
#define __IMU_APP_H

#include "config.h"
#include "MPU6500_SPI.h"
#include "imu_solution_quat.h"

#define MPU6500_SPI_NSS_High()              (NSS_PIN = 1)
#define MPU6500_SPI_NSS_Low()               (NSS_PIN = 0)

extern EulerAngle_t EulerAngle;

u8 imu_spi_write_1(u8 reg, u8 dat);
u8 imu_spi_write_2(u8 reg, u8 dat);
u8 imu_spi_read_1(u8 reg, u8 *buf, u16 len);
u8 imu_spi_read_2(u8 reg, u8 *buf, u16 len);

void IMU_Init(void);
void IMU_Update(void);

#endif // !__IMU_APP_H
