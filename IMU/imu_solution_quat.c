
#include "imu_solution_quat.h"
#include "user_lib.h"
#include <math.h>

#include "MPU6500_SPI.h"


/**
 * @brief Update euler angle according to the imu data that just read.
 * @note  The frequency to execute this task is defined by halfT_s.
 * 
 * @param euler Pointer of euler angle struct
 * @param dat   Pointer of imu data struct
 */
void EulerAngleUpdate_Quat(EulerAngle_t *euler, IMU_Data_t *dat)
{
    // 采样周期
    // float halfT_s = ((float)t_ms / 1000.0f);

    // 四元素参数
    static float q_w = 1.0f;
    static float q_x = 0.0f;
    static float q_y = 0.0f;
    static float q_z = 0.0f;

    // 控制器参数
    static const float imu_Kp = 2.0f;    // 比例增益
    static const float imu_Ki = 0.005f;  // 积分增益
    static float integralFBx = 0.0f, integralFBy = 0.0f, integralFBz = 0.0f;

    // 将原始数据转换为弧度每秒和g
    float ax = dat->accx;
    float ay = dat->accy;
    float az = dat->accz;
    float gx = DEG_TO_RAD(dat->gyrox); // 转为rad/s;
    float gy = DEG_TO_RAD(dat->gyroy);
    float gz = DEG_TO_RAD(dat->gyroz);

    // 辅助变量
    float recipNorm;
    float halfvx, halfvy, halfvz;
    float halfex, halfey, halfez;
    float qa, qb, qc;

    // 加速度计数据校验
    if(ax*ay*az == 0) return;

    // 归一化加速度计测量值（必须先归一化）
    recipNorm = 1.0f / sqrt(ax * ax + ay * ay + az * az);
    ax *= recipNorm;
    ay *= recipNorm;
    az *= recipNorm;

    // 估计重力的方向
    halfvx = q_x * q_z - q_w * q_y;
    halfvy = q_w * q_x + q_y * q_z;
    halfvz = q_w * q_w - 0.5f + q_z * q_z;

    // 误差是估计方向和测量方向的叉积
    halfex = (ay * halfvz - az * halfvy);
    halfey = (az * halfvx - ax * halfvz);
    halfez = (ax * halfvy - ay * halfvx);

    // 计算并应用积分反馈
    if(imu_Ki > 0.0f) {
        integralFBx += imu_Ki * halfex * halfT_s;    // 积分误差比例增益
        integralFBy += imu_Ki * halfey * halfT_s;
        integralFBz += imu_Ki * halfez * halfT_s;
        gx += integralFBx;    // 应用积分反馈
        gy += integralFBy;
        gz += integralFBz;
    } else {
        integralFBx = 0.0f;   // 防止积分饱和
        integralFBy = 0.0f;
        integralFBz = 0.0f;
    }

    // 应用比例反馈
    gx += imu_Kp * halfex;
    gy += imu_Kp * halfey;
    gz += imu_Kp * halfez;

    // 四元数导数计算
    gx *= (0.5f * halfT_s);     // 预乘以减少操作
    gy *= (0.5f * halfT_s);
    gz *= (0.5f * halfT_s);
    qa = q_w;
    qb = q_x;
    qc = q_y;
    q_w += (-qb * gx - qc * gy - q_z * gz);
    q_x += (qa * gx + qc * gz - q_z * gy);
    q_y += (qa * gy - qb * gz + q_z * gx);
    q_z += (qa * gz + qb * gy - qc * gx);

    // 归一化四元数
    recipNorm = 1.0f / sqrt(q_w * q_w + q_x * q_x + q_y * q_y + q_z * q_z);
    q_w *= recipNorm;
    q_x *= recipNorm;
    q_y *= recipNorm;
    q_z *= recipNorm;

    // 计算欧拉角
    euler->pitch = RAD_TO_DEG(asin(2.0f * (q_w * q_y - q_z * q_x)));
    euler->roll = RAD_TO_DEG(atan2(2.0f * (q_w * q_x + q_y * q_z), 1.0f - 2.0f * (q_x * q_x + q_y * q_y)));
    euler->yaw = RAD_TO_DEG(atan2(2.0f * (q_w * q_z + q_x * q_y), 1.0f - 2.0f * (q_y * q_y + q_z * q_z)));
}
