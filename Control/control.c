
#include "control.h"
#include "key_ud.h"
#include "Joystick.h"
#include "imu_app.h"
#include "user_lib.h"
#include "Display.h"

#define Speed_Limit             LimAbsAsgn

// 把结构体中的结构体成员换成指针，减少结构体传参大小和内存对齐浪费空间大小
static ControlEulerOut_t ControlEuler = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
static ControlJoystick_t ControlJoystick = { 0.0f, 0.0f, 0.0f };
static ControlGravity_t  ControlGravity  = { 0.0f, 0.0f, 0.0f };

ControlCar_t ctrl_car =
{
    Ctrl_Mode_JoyStick,
    DEFAULT_VW,
    &ControlEuler,
    &ControlJoystick,
    &ControlGravity
};

#if 0
/**
 * @brief 设置小车模式
 * 
 * @param mode 模式
 */
void Control_SetMode(ControlMode_t mode)
{
    ctrl_car.mode = mode;
}
#endif

void Control_ModeInc(void)
{
    ++ctrl_car.mode >= Ctrl_Mode_TOTAL ? ctrl_car.mode = 0 : (void)0;
}

void Control_ModeDec(void)
{
    ctrl_car.mode == 0 ? ctrl_car.mode = (Ctrl_Mode_TOTAL - 1) : ctrl_car.mode--;
}

/**
 * @brief 读取当前控制模式。
 * 
 * @return ControlMode_t 当前模式
 */
u8 Control_GetMode(void)
{
    return (u8)ctrl_car.mode;
}

#if 0
/**
 * @brief 设置小车摇杆模式下的旋转速度
 * 
 * @param vw 旋转速度大小 (0 ~ 100)
 */
void Control_SetVw(float vw)
{
    ctrl_car.vw_set = vw;
}
#endif

void Control_VWInc(void)
{
    ctrl_car.vw_set < 100 ? ctrl_car.vw_set += 10 : (void)0;
}

void Control_VWDec(void)
{
    ctrl_car.vw_set > 10 ? ctrl_car.vw_set -= 10 : (void)0;
}

/**
 * @brief 读取小车当前转向速度。
 * 
 * @return s32 转向速度
 */
s32  Control_GetVw(void)
{
    return (s32)ctrl_car.vw_set;
}

/**
 * @brief 更新控制数据
 * 
 */
void Control_Update(void)
{
    if (ShowState == PAGE_Control && Page_Control_State == Page_Control_State_PLAY)
    {
        switch (ctrl_car.mode)
        {
            case Ctrl_Mode_JoyStick:
            {
                // 速度直接来自摇杆
                ctrl_car.joystick->vx = ((s16)ADC_ZERO - (s16)adc_data.adc_ch0) / (float)ADC_ZERO * SPEED_LIMIT;
                ctrl_car.joystick->vy = ((s16)ADC_ZERO - (s16)adc_data.adc_ch1) / (float)ADC_ZERO * SPEED_LIMIT;

                ABS(ctrl_car.joystick->vx) < SPEED_DEAD ? ctrl_car.joystick->vx = 0.0f : (void)0;
                ABS(ctrl_car.joystick->vy) < SPEED_DEAD ? ctrl_car.joystick->vy = 0.0f : (void)0;

                // vw 由按键按下而改变
                // vw 目前只有前进和后退，而不是在原有的 vm 数值 基础上改动
                if (KeyUD_Is_Pressed(Key_L_Now)) {
                    ctrl_car.joystick->vw = (float)ctrl_car.vw_set;
                }
                else if (KeyUD_Is_Pressed(Key_R_Now)) {
                    ctrl_car.joystick->vw = -(float)ctrl_car.vw_set;
                }
                else {
                    ctrl_car.joystick->vw = 0;
                }

                // 这里限制最大速度
                Speed_Limit(ctrl_car.joystick->vx, SPEED_LIMIT);
                Speed_Limit(ctrl_car.joystick->vy, SPEED_LIMIT);
                Speed_Limit(ctrl_car.joystick->vw, SPEED_LIMIT);
            } break;

            // 本意是想让 Yaw 角度用cos和sin获得vx和vy, 这样更符合直觉, 但是没有对应的函数
            // 使用 Pitch 来决定 vm 会更符合直觉
            case Ctrl_Mode_Gravity:
            {
                // roll 决定 vx
                ctrl_car.gravity->vx = MapAngleTo100(ctrl_car.euler->roll, ROLL_ANGLE_USE);
                // pitch 决定 vy
                ctrl_car.gravity->vy = MapAngleTo100(ctrl_car.euler->pitch, PITCH_ANGLE_USE);
                // yaw 决定 vw
                ctrl_car.gravity->target_yaw = ctrl_car.euler->yaw;

                // 这里限制最大速度
                Speed_Limit(ctrl_car.gravity->vx, SPEED_LIMIT);
                Speed_Limit(ctrl_car.gravity->vy, SPEED_LIMIT);
            } break;
            
            default: break;
        }
    }
    else
    {
        ctrl_car.joystick->vx = 0;
        ctrl_car.joystick->vy = 0;
        ctrl_car.joystick->vw = 0;
        ctrl_car.gravity->vx = 0;
        ctrl_car.gravity->vy = 0;
        ctrl_car.gravity->target_yaw = 0;
    }
}


/**
 * @brief 计算控制欧拉角，即使现在没在遥控状态。
 * @note  放在欧拉角读取完之后执行即可。
 * 
 */
void Control_UpdateEuler(void)
{
    ctrl_car.euler->roll = EulerAngle.roll;
    ctrl_car.euler->pitch = Lim_Ang_180(EulerAngle.pitch + ctrl_car.euler->pitch_bias);
    ctrl_car.euler->yaw = Lim_Ang_180(EulerAngle.yaw + ctrl_car.euler->yaw_bias);
}

/**
 * @brief 把偏航角的偏差补上。
 * 
 * @param yaw_current   当前的偏航角。
 */
void Control_CalcYawBias(void)
{
    ctrl_car.euler->yaw_bias = -EulerAngle.yaw;
}

/**
 * @brief 将此时的俯仰角设置为零点。
 * 
 * @param pitch_current 此时的俯仰角。
 */
void Control_CalcPitchBias(void)
{
    ctrl_car.euler->pitch_bias = -EulerAngle.pitch;
}
