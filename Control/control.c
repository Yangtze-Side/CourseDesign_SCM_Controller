
#include "control.h"
#include "key_ud.h"
#include "Joystick.h"
#include "imu_app.h"


ControlCar ctrl_car;


/**
 * @brief 限制速度在指定范围内
 * @param val   要限制的变量地址（如 &ctrl_car.out_vx）
 * @param min   最小值
 * @param max   最大值
 */
void Speed_Limit(float *val, float min, float max)
{
    if (*val > max)
        *val = max;
    else if (*val < min)
        *val = min;
}

float MapAngleTo100(float angle)
{
    if (angle < 0) angle = 0;       // 限制范围
    if (angle > 30) angle = 30;

    return (angle * (100.0f / 30.0f));
}


void Control_Data_Update(void)
{
    ctrl_car.joystick.vx = (adc_data.adc_ch0 - 2048.0f) / 2048.0f * 100.0f;
    ctrl_car.joystick.vy = (adc_data.adc_ch1 - 2048.0f) / 2048.0f * 100.0f;

    ctrl_car.gravity.roll  = MapAngleTo100(EulerAngle.roll);
    ctrl_car.gravity.pitch = MapAngleTo100(EulerAngle.pitch);
    ctrl_car.gravity.yaw   = MapAngleTo100(EulerAngle.yaw);
}

void Control_Update(void)
{

    Control_Data_Update();

    switch (ctrl_car.mode)
    {
        case Ctrl_Mode_JoyStick:
            // 速度直接来自摇杆
            ctrl_car.out_vx = ctrl_car.joystick.vx;
            ctrl_car.out_vy = ctrl_car.joystick.vy;

            // vw 由按键按下而改变
            // vm 目前只有前进和后退，而不是在原有的 vm数值 基础上改动
            if (KeyUD_Is_Pressed(Key_UD_Left)) {
                ctrl_car.joystick.vw = 30;
            }
            else if (KeyUD_Is_Pressed(Key_UD_Right)) {
                ctrl_car.joystick.vw = -30;
            }
            else {
                ctrl_car.joystick.vw = 0;
            }
            ctrl_car.out_vw = ctrl_car.joystick.vw;
            break;

        // 本意是想让 Yaw 角度用cos和sin获得vx和vy, 这样更符合直觉, 但是没有对应的函数
        // 使用 Pitch 来决定 vm 会更符合直觉
        case Ctrl_Mode_Gravity:
            // roll 决定 vx
            ctrl_car.out_vx = ctrl_car.gravity.roll  * GRAVITY_SENSITY;
            // pitch 决定 vy
            ctrl_car.out_vy = ctrl_car.gravity.pitch * GRAVITY_SENSITY;
            // yaw 决定 vm
            ctrl_car.out_vw = ctrl_car.gravity.yaw * GRAVITY_SENSITY;

            break;

        default:
            ctrl_car.out_vx = 0.0f;
            ctrl_car.out_vy = 0.0f;
            ctrl_car.out_vw = 0.0f;
            
            break;    
    }

    // 这里限制最大速度
    Speed_Limit(&ctrl_car.out_vx, -(SPEED_LIMIT), SPEED_LIMIT);
    Speed_Limit(&ctrl_car.out_vy, -(SPEED_LIMIT), SPEED_LIMIT);
    Speed_Limit(&ctrl_car.out_vw, -(SPEED_LIMIT), SPEED_LIMIT);
}
