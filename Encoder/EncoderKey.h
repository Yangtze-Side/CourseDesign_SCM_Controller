#ifndef __ENCODERKEY_H
#define __ENCODERKEY_H

#define TASK_CYCLE_MS        20       // 与任务周期一致，单位：ms
// 每转过这么多步长就触发一次按键事件
#define STEP_THRESHOLD       20

// 每ms转过的角度
#define SPEED_STEP_ONE      0.1
#define SPEED_STEP_TWO      0.15
#define SPEED_STEP_THREE    0.2
// 对应的加速度倍率
#define ACC_ONE            0.8
#define ACC_TWO            0.7
#define ACC_THREE          0.6 

void EncoderKey_Update(void);
void EncoderKey_Init(void);

#endif // !__ENCODERKEY_H