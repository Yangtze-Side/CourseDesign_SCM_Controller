
#include "imu_def.h"
#include "user_lib.h"


/**
 * @brief Add euler angle bias to the final result.
 * 
 * @param e EulerAngle structure pionter.
 */
void EulerAngle_AddBias(EulerAngle_t *e)
{
    e->yaw = Lim_Ang_180(e->yaw - e->yaw_bias);
    e->pitch = Lim_Ang_180(e->pitch - e->pitch_bias);
}


/**
 * @brief The Yaw is corrected to 0 degrees according to current yaw.
 * 
 * @param e EulerAngle structure pionter.
 */
void EulerAngle_ClearYaw(EulerAngle_t *e)
{
    e->yaw_bias = Lim_Ang_180(e->yaw_bias + e->yaw);
}


/**
 * @brief The Pitch is corrected to 0 degrees according to current pitch,
 *        and the device is considered upright.
 * 
 * @param e EulerAngle structure pionter.
 */
void EulerAngle_ClearPitch(EulerAngle_t *e)
{
    e->pitch_bias = Lim_Ang_180(e->pitch_bias + e->pitch);
}
