#include "MotionAnalysis.h"

int MoveSpeedFactor=15000;
int RotateSpeedFactor=2000;
int TranslateSpeedFactor=2000;
unsigned char MoveMask=WHEEL_MASK_EMPTY;
unsigned char TranslateMask=WHEEL_MASK_EMPTY;
unsigned char RotateMask=WHEEL_MASK_EMPTY;

PIDInstance WheelPIDInstance[4];

void ApplyMaskWithFactor(int *speed,unsigned char mask,int Factor);

void MontionAnalysisConfig()
{
	InitOnePIDInstance(WheelPIDInstance+0,0,0.01,0.1,0);
	InitOnePIDInstance(WheelPIDInstance+1,0,0.01,0.1,0);
	InitOnePIDInstance(WheelPIDInstance+2,0,0.01,0.1,0);
	InitOnePIDInstance(WheelPIDInstance+3,0,0.01,0.1,0);
}

void MotionAnalysisDirectSet(int speed,unsigned char WHEEL_MASK)
{
	int	rotation[4]={0};
	rotation[0]= ((WHEEL_MASK & 0x80?1:0) - (WHEEL_MASK & 0x08?1:0));
	WHEEL_MASK<<=1;
	rotation[1]= ((WHEEL_MASK & 0x80?1:0) - (WHEEL_MASK & 0x08?1:0));
	WHEEL_MASK<<=1; 
	rotation[2]= ((WHEEL_MASK & 0x80?1:0) - (WHEEL_MASK & 0x08?1:0));
	WHEEL_MASK<<=1;
	rotation[3]= ((WHEEL_MASK & 0x80?1:0) - (WHEEL_MASK & 0x08?1:0));
	WHEEL_MASK<<=1;
	SetMontorSpeed(rotation[0]*speed,&MONTOR_FRONT_LEFT);
	SetMontorSpeed(rotation[1]*speed,&MONTOR_FRONT_RIGHT);
	SetMontorSpeed(rotation[2]*speed,&MONTOR_BACK_LEFT);
	SetMontorSpeed(rotation[3]*speed,&MONTOR_BACK_RIGHT);
}

void MotionAnalysisOnStep(void)
{
	int speed[4]={0};
	ApplyMaskWithFactor(speed,MoveMask,MoveSpeedFactor);
	ApplyMaskWithFactor(speed,TranslateMask,TranslateSpeedFactor);
	ApplyMaskWithFactor(speed,RotateMask,RotateSpeedFactor);
	//范围矫正 结果不应该大于电机的最大设定值 限制Movespeedfactor的大小
	//。。。
	
	//调用PID控制器计算速度值
	WheelPIDInstance[0].goal=speed[0];
	WheelPIDInstance[1].goal=speed[1];
	WheelPIDInstance[2].goal=speed[2];
	WheelPIDInstance[3].goal=speed[3];
	
	speed[0] = FinishOnePIDStep((WheelPIDInstance+0),GetMontorSpeed(&MONTOR_FRONT_LEFT));
	speed[1] = FinishOnePIDStep((WheelPIDInstance+1),GetMontorSpeed(&MONTOR_FRONT_RIGHT));
	speed[2] = FinishOnePIDStep((WheelPIDInstance+2),GetMontorSpeed(&MONTOR_BACK_LEFT));
	speed[3] = FinishOnePIDStep((WheelPIDInstance+3),GetMontorSpeed(&MONTOR_BACK_RIGHT));

	for(int i=0;i<4;i++)
	{
		if((speed[i]>0?speed[i]:-speed[i])>20000)
		{
			speed[i]=speed[i]>0?20000:-20000;
		}
	}
	//设置电机速度
	SetMontorSpeed(speed[0],&MONTOR_FRONT_LEFT);
	SetMontorSpeed(speed[1],&MONTOR_FRONT_RIGHT);
	SetMontorSpeed(speed[2],&MONTOR_BACK_LEFT);
	SetMontorSpeed(speed[3],&MONTOR_BACK_RIGHT);
	
	ResetEncoderNum();
}

void ApplyMaskWithFactor(int *speed,unsigned char mask,int Factor)
{
	*(speed+0) += Factor * ((mask & 0x80?1:0) - (mask & 0x08?1:0));
	mask<<=1;
	*(speed+1) += Factor * ((mask & 0x80?1:0) - (mask & 0x08?1:0));
	mask<<=1;
	*(speed+2) += Factor * ((mask & 0x80?1:0) - (mask & 0x08?1:0));
	mask<<=1;
	*(speed+3) += Factor * ((mask & 0x80?1:0) - (mask & 0x08?1:0));
}


