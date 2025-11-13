
#include "user_math.h"
#include "math.h"


/**
 * @brief 角度加权函数。
 * 
 * @param ang1 角度 1
 * @param ang2 角度 2
 * @param wgh1 角度 1 的权重
 * @return float 加权之后的角度值（限制在 -180 ~ 180 度）
 */
float Weight_Ang(float ang1, float ang2, float wgh1)
{
    float diff, res;
    diff = ABS(ang1 - ang2);

    if (diff > 180.0f)
    {
        (ang1 < 0.0f) ? (ang1 += 360.0f) : (ang2 += 360.0f);
    }

    res = ang1 * wgh1 + ang2 * (1.0f - wgh1);
    return Lim_Ang_180(res);
}

/**
 * @brief 计算欧几里得距离。
 * 
 * @param x1 第一个点横坐标
 * @param y1 第一个点纵坐标
 * @param x2 第二个点横坐标
 * @param y2 第二个点纵坐标
 * @return float 欧几里得距离
 */
float Get_Dist(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}
