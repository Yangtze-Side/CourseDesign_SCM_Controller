#ifndef __USER_MATH_H
#define __USER_MATH_H

#include "config.h"

/*------------------------------------- Exported Defines ----------------------------------*/

#define ABS(x)	        ((x) < 0 ? -(x) : (x))          // 绝对值
#define min(a, b)       ((a) < (b) ? (a) : (b))         // 较小值
#define max(a, b)       ((a) > (b) ? (a) : (b))         // 较大值
#define mid(a, b, c)    ( (a) > (b) ?                       \
                          ((b) > (c) ? (b) : min(a, c)) :   \
                          ((a) > (c) ? (a) : min(b, c)) )       // 中间值

// 限制范围（不赋值）
#define Lim(x, min, max)        ( (x) < (min) ? (min) : ((x) > (max) ? (max) : (x)) )

// 限制范围（同时赋值）
#define LimAsgn(x, min, max)    ( (x) < (min) ? ((x) = (min)) : ((x) > (max) ? ((x) = (max)) : (x)) )
#define LimAbsAsgn(x, abs)      LimAsgn(x, -(abs), (abs))


/*-----------------------------------------------------------------------------------------*/

#ifndef PI
#define PI                  (3.1415926535898f)          // 圆周率
#endif

#define DEG_TO_RAD(x)       ((x) * PI / 180.0f)         // 角度转换为弧度
#define RAD_TO_DEG(x)       ((x) * 180.0f / PI)         // 弧度转换为角度


// 将 -360 ~ -180 度和 +180 ~ +360 度的角度限制在 -180 ~ +180 度（不会对 x 赋值）
#define Lim_Ang_180(x)    ((x) > 180.0f ? ((x) - 360.0f) : ((x) < -180.0f ? ((x) + 360.0f) : (x)))

// 根据两点坐标，获取第二个点之于第一个点的角度
#define Get_Angle(x2, y2, x1, y1)	(RAD_TO_DEG(atan2((y2) - (y1), (x2) - (x1))))



/*------------------------------------- Exported Functions ----------------------------------*/

float Weight_Ang(float ang1, float ang2, float wgh1);
float Get_Dist(float x1, float y1, float x2, float y2);


#endif // !__USER_MATH_H
