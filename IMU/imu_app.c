
#include "imu_app.h"
#include "user_def.h"
#include "user_spi.h"
#include "system.h"

// extern IWDG_HandleTypeDef hiwdg;
EulerAngle_t EulerAngle = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };


/**
 * @brief IMU write data to a specific register by SPI.
 * 
 * @param reg Register addr
 * @param dat Data byte to send
 * @return u8 FAILED or SUCCESS
 */
static u8 imu_spi_write(u8 reg, u8 dat)
{
    MPU6500_SPI_NSS_Low();      // Chip select
    if (User_SPI_Write(reg, 5) == User_SPI_TIMEOUT) return FAILED;
    if (User_SPI_Write(dat, 5) == User_SPI_TIMEOUT) return FAILED;
    MPU6500_SPI_NSS_High();     // Chip deselect

    return SUCCESS;
}

/**
 * @brief IMU read data form specific registers by SPI.
 * 
 * @param reg Register addr
 * @param buf Buffer of data bytes to read
 * @param len Length to read
 * @return u8 FAILED or SUCCESS
 */
static u8 imu_spi_read(u8 reg, u8 *buf, u16 len)
{
    MPU6500_SPI_NSS_Low();
    if (User_SPI_Write(reg, 5) == User_SPI_TIMEOUT) return FAILED;
    if (User_SPI_Read(buf, len, 10) == User_SPI_TIMEOUT) return FAILED;
    MPU6500_SPI_NSS_High();

    return SUCCESS;
}


/**
 * @brief Initialization of imu.
 * 
 * @return u8 FAILED or SUCCESS
 */
u8 IMU_Init(void)
{
    u8 retry = 10;
    u8 ret = SUCCESS;

    MPU6500_Func_t sfunc =
    {
        imu_spi_write,
        imu_spi_read
    };

    while (MPU6500_Init(&sfunc) == FAILED)
    {
        if (--retry == 0)
        {
            MPU6500_SET_BIT(MPU6500_State, MPU6500_InitFailed_BIT);
            ret = FAILED;
            break;
        }
        Sys_Delay(20);
        // HAL_IWDG_Refresh(&hiwdg);       // Clear the watch dog counter
    }
    
    return ret;
}


/**
 * @brief IMU task performed every halfT_s(defined in imu_solution_quat.h) ms.
 * @note  The frequency of this task is determined by quat analyze frequency,
 *        i.e. halfT_s, which is defined in imu_solution_quat.h.
 * 
 */
void IMU_Update(void)
{
    if (MPU6500_IsInitialized())
    {
        if (MPU6500_IsDriftSampled())
        {
            MPU6500_ReadData();                                     // Load data to 'MPU6500_Data'
            EulerAngleUpdate_Quat(&EulerAngle, &MPU6500_Data);      // Work out euler angle.
            EulerAngle_AddBias(&EulerAngle);                        // Add bias value.
        }
        else
        {
            MPU6500_SampleDrift();      // Sample drift upon initialization.
        }
    }
}
