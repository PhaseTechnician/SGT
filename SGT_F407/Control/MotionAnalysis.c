#include "MotionAnalysis.h"
#include "USART.h"
//当前不得大于320
int MoveSpeedFactor=0;
int RotateSpeedFactor=0;
int TranslateSpeedFactor=0;
unsigned char MoveMask=WHEEL_MASK_EMPTY;
unsigned char TranslateMask=WHEEL_MASK_EMPTY;
unsigned char RotateMask=WHEEL_MASK_EMPTY;

PIDInstance WheelPIDInstance[4];

void ApplyMaskWithFactor(int *speed,unsigned char mask,int Factor);

void MontionAnalysisConfig()
{
	InitOnePIDInstance(WheelPIDInstance+0,0,0.5,0,0);
	InitOnePIDInstance(WheelPIDInstance+1,0,0.5,0,0);
	InitOnePIDInstance(WheelPIDInstance+2,0,0.5,0,0);
	InitOnePIDInstance(WheelPIDInstance+3,0,0.5,0,0);	
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

/*
141M1
242M2
338M3
343M4
*/

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
	
	int feedBack1=GetMontorSpeed(&MONTOR_FRONT_LEFT);
	int feedBack2=GetMontorSpeed(&MONTOR_FRONT_RIGHT);
	int feedBack3=GetMontorSpeed(&MONTOR_BACK_LEFT);
	int feedBack4=GetMontorSpeed(&MONTOR_BACK_RIGHT);
	
	speed[0] = FinishOnePIDStep((WheelPIDInstance+0),feedBack1);
	speed[1] = FinishOnePIDStep((WheelPIDInstance+1),feedBack2);
	speed[2] = FinishOnePIDStep((WheelPIDInstance+2),feedBack3);
	speed[3] = FinishOnePIDStep((WheelPIDInstance+3),feedBack4);

	for(int i=0;i<4;i++)
	{
		if(speed[i]>20000)
		{
			speed[i]=20000;
		}
		else if(speed[i]<-20000)
		{
			speed[i]=-20000;
		}
	}
	//设置电机速度
	SetMontorSpeed(speed[0],&MONTOR_FRONT_LEFT);
	SetMontorSpeed(speed[1],&MONTOR_FRONT_RIGHT);
	SetMontorSpeed(speed[2],&MONTOR_BACK_LEFT);
	SetMontorSpeed(speed[3],&MONTOR_BACK_RIGHT);
	
	ResetEncoderNum();
	
	
	USART1SendNumInt(-feedBack1);
	USART1Send("M1\n");
	USART1SendNumInt(feedBack2);
	USART1Send("M2\n");
	USART1SendNumInt(feedBack3);
	USART1Send("M3\n");
	USART1SendNumInt(-feedBack4);
	USART1Send("M4\n");
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


