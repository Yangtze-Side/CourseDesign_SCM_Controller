
#include "FOC_Util.h"
#include "FOC_Math.h"
#include "user_pwm.h"

float dc_a, dc_b, dc_c;
float Ualpha=0.0f,Ubeta=0.0f;
volatile float Ua=0.0f,Ub=0.0f,Uc=0.0f;


void setPWM(float Ua, float Ub, float Uc)
{
	// 设置保护
	Ua = Lim(Ua, 0.0f, VOLTAGE_LIMIT);
	Ub = Lim(Ub, 0.0f, VOLTAGE_LIMIT);
	Uc = Lim(Uc, 0.0f, VOLTAGE_LIMIT);

	// 计算占空比
	// 限制占空比从0到1
	dc_a = Lim(Ua / VOLTAGE_POWER_SUPPLY, 0.0f , 1.0f );
	dc_b = Lim(Ub / VOLTAGE_POWER_SUPPLY, 0.0f , 1.0f );
	dc_c = Lim(Uc / VOLTAGE_POWER_SUPPLY, 0.0f , 1.0f );

	//写入PWM到PWM 0 1 2 通道
	User_PWMA_SetWidth(dc_a * PWM_PERIOD);
	User_PWMB_SetWidth(dc_b * PWM_PERIOD);
	User_PWMC_SetWidth(dc_c * PWM_PERIOD);
}


void setPhaseVoltage(float Uq, float angle_elctric, float zero_electric_angle) {
	angle_elctric = _normalizeAngle(angle_elctric - zero_electric_angle);

	// 帕克逆变换
	Ualpha =  -Uq*_sin(angle_elctric); 
	Ubeta =   Uq*_cos(angle_elctric); 

	// 克拉克逆变换
	Ua = Ualpha + VOLTAGE_POWER_SUPPLY/2;
	Ub = (_sqrtApprox(3)*Ubeta-Ualpha)/2 + VOLTAGE_POWER_SUPPLY/2;
	Uc = (-Ualpha-_sqrtApprox(3)*Ubeta)/2 + VOLTAGE_POWER_SUPPLY/2;

 	// 设置PWM
 	setPWM(Ua,Ub,Uc);
}


void setTorque(float Uq,float angle_elctric) {
	LimAbsAsgn(Uq, VOLTAGE_POWER_SUPPLY/2);
	angle_elctric = _normalizeAngle(angle_elctric);

	// 帕克逆变换
	Ualpha =  -Uq*_sin(angle_elctric); 
	Ubeta =   Uq*_cos(angle_elctric); 

	// 克拉克逆变换
	Ua = Ualpha + VOLTAGE_POWER_SUPPLY/2;
	Ub = (_sqrtApprox(3)*Ubeta-Ualpha)/2 + VOLTAGE_POWER_SUPPLY/2;
	Uc = (-Ualpha-_sqrtApprox(3)*Ubeta)/2 + VOLTAGE_POWER_SUPPLY/2;
	
	setPWM(Ua,Ub,Uc);
}
