
#include "control.h"


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


void Control_Update(void)
{
    switch (ctrl_car.mode)
    {
        case Ctrl_Mode_JoyStick:
            // 速度直接来自摇杆
            ctrl_car.out_vx = ctrl_car.joystick.vx;
            ctrl_car.out_vy = ctrl_car.joystick.vy;

            // vw 由按键按下而改变
            // vm 目前只有前进和后退，而不是在原有的 vm数值 基础上改动
            if (ctrl_car.joystick.btn_left) {
                ctrl_car.joystick.vw = 30;
            }
            else if (ctrl_car.joystick.btn_right) {
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
    }

    // 这里限制最大速度
    Speed_Limit(&ctrl_car.out_vx, -200.0f, 200.0f);
    Speed_Limit(&ctrl_car.out_vy, -200.0f, 200.0f);
}
