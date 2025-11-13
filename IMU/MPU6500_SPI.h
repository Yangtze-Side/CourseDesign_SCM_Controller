#ifndef __MPU6500_SPI_H
#define __MPU6500_SPI_H

#include "config.h"
#include "imu_def.h"

/*--------------------------------------- Exported Typedefs ---------------------------------------*/

typedef u8 (*MPU6500_SPI_WriteFunc)(u8 reg, u8 dat);
typedef u8 (*MPU6500_SPI_ReadFunc) (u8 reg, u8 xdata * pdat, u16 size);

typedef struct MPU6500_Func_t
{
    MPU6500_SPI_WriteFunc write;
    MPU6500_SPI_ReadFunc  read;
} MPU6500_Func_t;


// Full scale rage selection
typedef enum MPU6500_AccelFsr
{
    MPU6500_Accel_2g = 0,
    MPU6500_Accel_4g = 1,
    MPU6500_Accel_8g = 2,
    MPU6500_Accel_16g = 3
} MPU6500_AccelFsr;

typedef enum MPU6500_GyroFsr
{
    MPU6500_Gyro_250dps = 0,
    MPU6500_Gyro_500dps = 1,
    MPU6500_Gyro_1000dps = 2,
    MPU6500_Gyro_2000dps = 3
} MPU6500_GyroFsr;


/*--------------------------------------- Exported Constants --------------------------------------*/

#define MPU6500_CommunicationOK_BIT     0x01
#define MPU6500_Initialized_BIT         0x02
#define MPU6500_DriftSampled_BIT        0x04
#define MPU6500_InitFailed_BIT          0x08

#define MPU6500_CommunicationOK()       (MPU6500_State & MPU6500_CommunicationOK_BIT)
#define MPU6500_IsInitialized()         (MPU6500_State & MPU6500_Initialized_BIT)
#define MPU6500_IsDriftSampled()        (MPU6500_State & MPU6500_DriftSampled_BIT)
#define MPU6500_IsInitFailed()          (MPU6500_State & MPU6500_InitFailed_BIT)


#define MPU6500_SET_BIT(x, b)           ((x) |=  (b))
#define MPU6500_CLR_BIT(x, b)           ((x) &= ~(b))


/*------------------------------------- Exported Funcs & Vars -------------------------------------*/

extern u8 MPU6500_State;
extern IMU_Data_t MPU6500_Data;

u8   MPU6500_Init(MPU6500_Func_t *sFunc);
void MPU6500_ReadData(void);
void MPU6500_SampleDrift(void);


/*---------------------------------------- User Determine -----------------------------------------*/

// #define MPU6500_ADDR                    (0x68 << 1)
#define MPU6500_ACCEL_FSR               MPU6500_Accel_8g
#define MPU6500_GYRO_FSR                MPU6500_Gyro_1000dps
#define SampleRate_Hz                   200


#endif // !__MPU6500_SPI_H
