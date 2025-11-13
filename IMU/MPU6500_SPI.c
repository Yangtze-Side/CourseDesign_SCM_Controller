
#include "MPU6500_SPI.h"
#include "user_lib.h"


/*--------------------------------------- Library --------------------------------------*/

/*-------------------------------- Registers ---------------------------------*/

#define XG_OFFSET_H         0x13
#define XG_OFFSET_L         0x14
#define YG_OFFSET_H         0x15
#define YG_OFFSET_L         0x16
#define ZG_OFFSET_H         0x17
#define ZG_OFFSET_L         0x18

#define XA_OFFSET_H         0x77
#define XA_OFFSET_L         0x78
#define YA_OFFSET_H         0x7A
#define YA_OFFSET_L         0x7B
#define ZA_OFFSET_H         0x7D
#define ZA_OFFSET_L         0x7E

#define SMPLRT_DIV          0x19
#define CONFIG              0x1A
#define GYRO_CONFIG         0x1B
#define ACCEL_CONFIG        0x1C
#define ACCEL_CONFIG2       0x1D        // 保持默认值 0 即可，不用配置

#define ACCEL_XOUT_H        0x3B
#define GYRO_XOUT_H         0x43

#define PWR_MGMT_1          0x6B
#define PWR_MGMT_2          0x6C
#define WHO_AM_I            0x75

// #define INT_PIN_CONFIG      0x37
// #define INT_ENABLE          0x38

#define USER_CTRL           0x6A

/*-------------------------------- Constants ---------------------------------*/

// #define WHO_AM_I_VAL        0x68
#define WHO_AM_I_VAL        0x70
#define PWR_MGMT_1_VAL      0x01
#define PWR_MGMT_2_VAL      0x00

#define CLK_FREQ_Hz         1000
#if (SampleRate_Hz > CLK_FREQ_Hz)
# error SampleRate_Hz should be no more than CLK_FREQ_Hz
#endif
#define SMPLRT_DIV_VAL      ((u8)(CLK_FREQ_Hz / SampleRate_Hz - 1))

// #define INT_PIN_CONFIG_VAL  0x00
// #define INT_ENABLE_VAL      0x01

#define USER_CTRL_VAL       0x10


#define ACCEL_2G_TRANSFACTOR        (2.0f / 32768.0f)
#define ACCEL_4G_TRANSFACTOR        (4.0f / 32768.0f)
#define ACCEL_8G_TRANSFACTOR        (8.0f / 32768.0f)
#define ACCEL_16G_TRANSFACTOR       (16.0f / 32768.0f)

#define GYRO_250DPS_TRANSFACTOR     (250.0f / 32768.0f)
#define GYRO_500DPS_TRANSFACTOR     (500.0f / 32768.0f)
#define GYRO_1000DPS_TRANSFACTOR    (1000.0f / 32768.0f)
#define GYRO_2000DPS_TRANSFACTOR    (2000.0f / 32768.0f)

#define TEMP_TRANS_FACTOR           (340.0f)

#define DriftSample_AMOUNT          (500)       // Amount of data sample during offset sampling

/*---------------------------------- Macros -----------------------------------*/

#define ACCEL_Trans(acc_raw)        ((float)(acc_raw) * acc_trans_factor)
#define GYRO_Trans(gyro_raw)        ((float)(gyro_raw) * gyro_trans_factor)
#define TEMP_Trans(temp_raw)        ((float)(temp_raw) / TEMP_TRANS_FACTOR + 36.53f)

/*---------------------------------- Types -----------------------------------*/

typedef enum mpu_lpf_t
{
    MPU_FILTER_250HZ = 0,       // delay: 0.97 ms
    MPU_FILTER_184HZ,           // delay: 2.9 ms
    MPU_FILTER_92HZ,            // delay: 3.9 ms
    MPU_FILTER_41HZ,            // delay: 5.9 ms
    MPU_FILTER_20HZ,            // delay: 9.9 ms
    MPU_FILTER_10HZ,            // delay: 17.85 ms
    MPU_FILTER_5HZ,             // delay: 33.48 ms
    MPU_FILTER_3600HZ,          // delay: 0.17 ms
} mpu_lpf_t;

/**
 * @brief Drift sample struct. Store drift sum value, then calculate the average
 *        and push it into GYRO_OFFS and ACC_OFFS register.
 * 
 */
typedef struct Drift_t
{
    s32 ax;
    s32 ay;
    s32 az;

    s32 gx;
    s32 gy;
    s32 gz;
} Drift_t;

/*-------------------------------- Variables ---------------------------------*/

static MPU6500_Func_t mpu6500_func = { NULL, NULL };
u8 MPU6500_State = 0x00;
IMU_Data_t MPU6500_Data = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
static float acc_trans_factor = ACCEL_8G_TRANSFACTOR, gyro_trans_factor = GYRO_1000DPS_TRANSFACTOR;

/*-------------------------------- Private Functions ---------------------------------*/

static u8 mpu_set_accel_fsr(MPU6500_AccelFsr fsr)
{
    u8 regval = ((u8)fsr << 3);
    if (mpu6500_func.write(ACCEL_CONFIG, regval) == FAILED) return FAILED;

    switch (fsr)
    {
        case MPU6500_Accel_2g: acc_trans_factor = ACCEL_2G_TRANSFACTOR; break;
        case MPU6500_Accel_4g: acc_trans_factor = ACCEL_4G_TRANSFACTOR; break;
        case MPU6500_Accel_8g: acc_trans_factor = ACCEL_8G_TRANSFACTOR; break;
        case MPU6500_Accel_16g: acc_trans_factor = ACCEL_16G_TRANSFACTOR; break;

        default: acc_trans_factor = ACCEL_8G_TRANSFACTOR; break;
    }
    return SUCCESS;
}

static u8 mpu_set_gyro_fsr(MPU6500_GyroFsr fsr)
{
    u8 regval = ((u8)fsr << 3);
    if (mpu6500_func.write(GYRO_CONFIG, regval) == FAILED) return FAILED;

    switch (fsr)
    {
        case MPU6500_Gyro_250dps: gyro_trans_factor = GYRO_250DPS_TRANSFACTOR; break;
        case MPU6500_Gyro_500dps: gyro_trans_factor = GYRO_500DPS_TRANSFACTOR; break;
        case MPU6500_Gyro_1000dps: gyro_trans_factor = GYRO_1000DPS_TRANSFACTOR; break;
        case MPU6500_Gyro_2000dps: gyro_trans_factor = GYRO_2000DPS_TRANSFACTOR; break;

        default: gyro_trans_factor = GYRO_1000DPS_TRANSFACTOR; break;
    }
    return SUCCESS;
}

static u8 mpu_set_dlpf(u16 lpf)
{
    u8 dat;

    if (lpf >= 3600)
        dat = MPU_FILTER_3600HZ;
    else if (lpf >= 250)
        dat = MPU_FILTER_250HZ;
    else if (lpf >= 184)
        dat = MPU_FILTER_184HZ;
    else if (lpf >= 92)
        dat = MPU_FILTER_92HZ;
    else if (lpf >= 41)
        dat = MPU_FILTER_41HZ;
    else if (lpf >= 20)
        dat = MPU_FILTER_20HZ;
    else if (lpf >= 10)
        dat = MPU_FILTER_10HZ;
    else
        dat = MPU_FILTER_5HZ;

    return mpu6500_func.write(CONFIG, dat);
}


/*-------------------------------- Public Functions ---------------------------------*/

/**
 * @brief Set mpu6500 i2c communicatin functions and configure mpu6500.
 * 
 * @param sFunc MPU6500_Func_t structure.
 */
u8 MPU6500_Init(MPU6500_Func_t *sFunc)
{
    u8 res;
    mpu6500_func = *sFunc;

    if (mpu6500_func.write(USER_CTRL, USER_CTRL_VAL) == FAILED) return FAILED;

    mpu6500_func.read(WHO_AM_I, &res, 1);
    if (res != WHO_AM_I_VAL) return FAILED;
    MPU6500_SET_BIT(MPU6500_State, MPU6500_CommunicationOK_BIT);

    if (mpu6500_func.write(PWR_MGMT_1, PWR_MGMT_1_VAL) == FAILED) return FAILED;
    if (mpu6500_func.write(PWR_MGMT_2, PWR_MGMT_2_VAL) == FAILED) return FAILED;
    if (mpu6500_func.write(SMPLRT_DIV, SMPLRT_DIV_VAL) == FAILED) return FAILED;

    if (mpu_set_accel_fsr(MPU6500_ACCEL_FSR) == FAILED) return FAILED;
    if (mpu_set_gyro_fsr(MPU6500_GYRO_FSR) == FAILED) return FAILED;
    if (mpu_set_dlpf(SampleRate_Hz >> 1) == FAILED) return FAILED;

    // if (mpu6500_func.write(INT_PIN_CONFIG, INT_PIN_CONFIG_VAL) == FAILED) return FAILED;
    // if (mpu6500_func.write(INT_ENABLE, INT_ENABLE_VAL) == FAILED) return FAILED;

    MPU6500_SET_BIT(MPU6500_State, MPU6500_Initialized_BIT);
    return SUCCESS;
}


/**
 * @brief Read data from mpu6500 data registers and transform into physical unit.
 * 
 */
void MPU6500_ReadData(void)
{
    u8 buf[14];
    s16 tmp;
    mpu6500_func.read(ACCEL_XOUT_H, buf, sizeof(buf));

    tmp = (s16)MAKEWORD(buf[0], buf[1]);
    MPU6500_Data.accx = ACCEL_Trans(tmp);
    tmp = (s16)MAKEWORD(buf[2], buf[3]);
    MPU6500_Data.accy = ACCEL_Trans(tmp);
    tmp = (s16)MAKEWORD(buf[4], buf[5]);
    MPU6500_Data.accz = ACCEL_Trans(tmp);
    
    tmp = (s16)MAKEWORD(buf[6], buf[7]);
    MPU6500_Data.temp = TEMP_Trans(tmp);

    tmp = (s16)MAKEWORD(buf[8], buf[9]);
    MPU6500_Data.gyrox = GYRO_Trans(tmp);
    tmp = (s16)MAKEWORD(buf[10], buf[11]);
    MPU6500_Data.gyroy = GYRO_Trans(tmp);
    tmp = (s16)MAKEWORD(buf[12], buf[13]);
    MPU6500_Data.gyroz = GYRO_Trans(tmp);
}


/**
 * @brief Sample gyro z offset, at an amount of 'DriftSample_AMOUNT'.
 * @note  Only execute when imu initializes.
 *        Sample time it takes is (DriftSample_AMOUNT / SampleRate_Hz).
 * 
 */
void MPU6500_SampleDrift(void)
{
    static u16 cnt = 0;
    static Drift_t drift = { 0, 0, 0, 0, 0, 0 };
    u8 buf[14];

    mpu6500_func.read(ACCEL_XOUT_H, buf, sizeof(buf));

    drift.ax += (s16)MAKEWORD(buf[0], buf[1]);
    drift.ay += (s16)MAKEWORD(buf[2], buf[3]);
    drift.az += (s16)MAKEWORD(buf[4], buf[5]);
    drift.gx += (s16)MAKEWORD(buf[8], buf[9]);
    drift.gy += (s16)MAKEWORD(buf[10], buf[11]);
    drift.gz += (s16)MAKEWORD(buf[12], buf[13]);

    if (++cnt >= DriftSample_AMOUNT)
    {
        // When sample process is over, push the drift value to MPU6500,
        // MPU6500 will apply zero-drifting bias to sensor data automatically.
        cnt = 0;
        
        drift.ax /= (s32)DriftSample_AMOUNT;
        drift.ay /= (s32)DriftSample_AMOUNT;
        drift.az /= (s32)DriftSample_AMOUNT;
        drift.gx /= (s32)DriftSample_AMOUNT;
        drift.gy /= (s32)DriftSample_AMOUNT;
        drift.gz /= (s32)DriftSample_AMOUNT;

        mpu6500_func.write(XA_OFFSET_H, HIBYTE(drift.ax));
        mpu6500_func.write(XA_OFFSET_L, LOBYTE(drift.ax));
        mpu6500_func.write(YA_OFFSET_H, HIBYTE(drift.ay));
        mpu6500_func.write(YA_OFFSET_L, LOBYTE(drift.ay));
        mpu6500_func.write(ZA_OFFSET_H, HIBYTE(drift.az));
        mpu6500_func.write(ZA_OFFSET_L, LOBYTE(drift.az));
        
        mpu6500_func.write(XG_OFFSET_H, HIBYTE(drift.gx));
        mpu6500_func.write(XG_OFFSET_L, LOBYTE(drift.gx));
        mpu6500_func.write(YG_OFFSET_H, HIBYTE(drift.gy));
        mpu6500_func.write(YG_OFFSET_L, LOBYTE(drift.gy));
        mpu6500_func.write(ZG_OFFSET_H, HIBYTE(drift.gz));
        mpu6500_func.write(ZG_OFFSET_L, LOBYTE(drift.gz));

        MPU6500_SET_BIT(MPU6500_State, MPU6500_DriftSampled_BIT);

        // To do
        // LED_SetTogglePeriod(125);
    }
}
