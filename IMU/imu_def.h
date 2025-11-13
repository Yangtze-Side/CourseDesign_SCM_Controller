#ifndef __IMU_DEF_H
#define __IMU_DEF_H

#include "def.h"


typedef struct IMU_Data_t
{
    float accx;
    float accy;
    float accz;
    float gyrox;
    float gyroy;
    float gyroz;
    float temp;
} IMU_Data_t;

typedef struct EulerAngle_t
{
    float pitch;
    float roll;
    float yaw;

    float pitch_bias;
    float yaw_bias;
} EulerAngle_t;


void EulerAngle_AddBias(EulerAngle_t *e);
void EulerAngle_ClearYaw(EulerAngle_t *e);
void EulerAngle_ClearPitch(EulerAngle_t *e);

#endif // !__IMU_DEF_H
