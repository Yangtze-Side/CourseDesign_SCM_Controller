
#include "control.h"
#include "key_ud.h"
#include "Joystick.h"
#include "imu_app.h"
#include "user_lib.h"


u8 vw_set;
ControlCar_t ctrl_car;


#define Angle_Limit             LimAbsAsgn
#define Speed_Limit             LimAbsAsgn


/**
 * @brief 更新控制数据
 * 
 */
void Control_Data_Update(void)
{
    ctrl_car.joystick.vx = (adc_data.adc_ch0 - 2048.0f) / 2048.0f * 100.0f;
    ctrl_car.joystick.vy = (adc_data.adc_ch1 - 2048.0f) / 2048.0f * 100.0f;

    ctrl_car.gravity.roll  = MapAngleTo100(EulerAngle.roll, ROLL_ANGLE_USE);
    ctrl_car.gravity.pitch = MapAngleTo100(EulerAngle.pitch, PITCH_ANGLE_USE);
    ctrl_car.gravity.yaw   = MapAngleTo100(EulerAngle.yaw, YAW_ANGLE_USE);
}

/**
 * @brief 更新控制总输出
 * 
 */
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
                ctrl_car.joystick.vw = vw_set;
            }
            else if (KeyUD_Is_Pressed(Key_UD_Right)) {
                ctrl_car.joystick.vw = -vw_set;
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
    Speed_Limit(ctrl_car.out_vx, SPEED_LIMIT);
    Speed_Limit(ctrl_car.out_vy, SPEED_LIMIT);
    Speed_Limit(ctrl_car.out_vw, SPEED_LIMIT);
}
