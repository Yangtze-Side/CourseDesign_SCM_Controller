
#include "control.h"
#include "key_ud.h"
#include "Joystick.h"
#include "imu_app.h"
#include "user_lib.h"

#define Speed_Limit             LimAbsAsgn


ControlCar_t ctrl_car =
{
    Ctrl_Mode_JoyStick,
    DEFAULT_VW,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
};


/**
 * @brief 设置小车模式
 * 
 * @param mode 模式
 */
void Control_Set_Mode(ControlMode_t mode)
{
    ctrl_car.mode = mode;
}

/**
 * @brief 设置小车摇杆模式下的旋转速度
 * 
 * @param vw 旋转速度大小 (0 ~ 100)
 */
void Control_SetVw(float vw)
{
    ctrl_car.vw_set = vw;
}

/**
 * @brief 更新控制数据
 * 
 */
void Control_Update(void)
{
    switch (ctrl_car.mode)
    {
        case Ctrl_Mode_JoyStick:
        {
            // 速度直接来自摇杆
            ctrl_car.joystick.vx = (adc_data.adc_ch0 - 2048.0f) / 2048.0f * 100.0f;
            ctrl_car.joystick.vy = (adc_data.adc_ch1 - 2048.0f) / 2048.0f * 100.0f;

            // vw 由按键按下而改变
            // vw 目前只有前进和后退，而不是在原有的 vm 数值 基础上改动
            if (KeyUD_Is_Pressed(Key_UD_Left)) {
                ctrl_car.joystick.vw = ctrl_car.vw_set;
            }
            else if (KeyUD_Is_Pressed(Key_UD_Right)) {
                ctrl_car.joystick.vw = -ctrl_car.vw_set;
            }
            else {
                ctrl_car.joystick.vw = 0;
            }

            // 这里限制最大速度
            Speed_Limit(ctrl_car.joystick.vx, SPEED_LIMIT);
            Speed_Limit(ctrl_car.joystick.vy, SPEED_LIMIT);
            Speed_Limit(ctrl_car.joystick.vw, SPEED_LIMIT);
        } break;

        // 本意是想让 Yaw 角度用cos和sin获得vx和vy, 这样更符合直觉, 但是没有对应的函数
        // 使用 Pitch 来决定 vm 会更符合直觉
        case Ctrl_Mode_Gravity:
        {
            // roll 决定 vx
            ctrl_car.gravity.vx = MapAngleTo100(EulerAngle.roll, ROLL_ANGLE_USE);
            // pitch 决定 vy
            ctrl_car.gravity.vy = MapAngleTo100(EulerAngle.pitch, PITCH_ANGLE_USE);
            // yaw 决定 vw
            ctrl_car.gravity.target_yaw = EulerAngle.yaw, YAW_ANGLE_USE;

            // 这里限制最大速度
            Speed_Limit(ctrl_car.gravity.vx, SPEED_LIMIT);
            Speed_Limit(ctrl_car.gravity.vy, SPEED_LIMIT);
        } break;

        default: break;
    }
}
