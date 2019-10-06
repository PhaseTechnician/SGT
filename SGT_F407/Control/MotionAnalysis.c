#include "MotionAnalysis.h"
unsigned char orientation;
unsigned int speed;

//�°汾�ۺ��˶�����ϵͳ
int MoveSpeedFactor;
int RotateSpeedFactor;
int TranslateSpeedFactor;
unsigned char MoveMask;
unsigned char TranslateMask;
unsigned char RotateMask;

PIDInstance WheelPIDInstance[4];

void ApplyMaskWithFactor(int *speed,unsigned char mask,int Factor);

void MontionAnalysisConfig()
{
	InitOnePIDInstance(WheelPIDInstance+0,0,0,0,0);
	InitOnePIDInstance(WheelPIDInstance+1,0,0,0,0);
	InitOnePIDInstance(WheelPIDInstance+2,0,0,0,0);
	InitOnePIDInstance(WheelPIDInstance+3,0,0,0,0);
}

void SetOrientation(unsigned char LocalOrientation)
{
	orientation = LocalOrientation;
	SetMontorRotation(LocalOrientation&0b00001000,&MONTOR_FRONT_LEFT);
	SetMontorRotation(LocalOrientation&0b00000100,&MONTOR_FRONT_RIGHT);
	SetMontorRotation(LocalOrientation&0b00000010,&MONTOR_BACK_LEFT);
	SetMontorRotation(LocalOrientation&0b00000001,&MONTOR_BACK_RIGHT);
}

inline void SetSpeed(unsigned int LineSpeed)
{
	speed = LineSpeed;
}

void MotionAnalysisOnStep(void)
{
	//basic
	SetMontorSpeed(speed,&MONTOR_FRONT_LEFT);
	SetMontorSpeed(speed,&MONTOR_FRONT_RIGHT);
	SetMontorSpeed(speed,&MONTOR_BACK_LEFT);
	SetMontorSpeed(speed,&MONTOR_BACK_RIGHT);
	//high level
	/*
	int speed[4]={0};
	ApplyMaskWithFactor(speed,MoveMask,MoveSpeedFactor);
	ApplyMaskWithFactor(speed,TranslateMask,TranslateSpeedFactor);
	ApplyMaskWithFactor(speed,RotateMask,RotateSpeedFactor);
	//��Χ���� �����Ӧ�ô��ڵ��������趨ֵ ����Movespeedfactor�Ĵ�С
	//������
	
	//����PID�����������ٶ�ֵ
	speed[0] = FinishOnePIDStep((WheelPIDInstance+0),GetMontorSpeed(&MONTOR_FRONT_LEFT));
	speed[1] = FinishOnePIDStep((WheelPIDInstance+1),GetMontorSpeed(&MONTOR_FRONT_RIGHT));
	speed[2] = FinishOnePIDStep((WheelPIDInstance+2),GetMontorSpeed(&MONTOR_BACK_LEFT));
	speed[3] = FinishOnePIDStep((WheelPIDInstance+3),GetMontorSpeed(&MONTOR_BACK_RIGHT));
	//���õ���ٶ�
	SetMontorSpeed(speed[0],&MONTOR_FRONT_LEFT);
	SetMontorSpeed(speed[1],&MONTOR_FRONT_RIGHT);
	SetMontorSpeed(speed[2],&MONTOR_BACK_LEFT);
	SetMontorSpeed(speed[3],&MONTOR_BACK_RIGHT);
	*/
}

void ApplyMaskWithFactor(int *speed,unsigned char mask,int Factor)
{
	*(speed+0) += Factor * (mask & 0x80 - mask & 0x08);
	mask<<=1;
	*(speed+1) += Factor * (mask & 0x80 - mask & 0x08);
	mask<<=1;
	*(speed+2) += Factor * (mask & 0x80 - mask & 0x08);
	mask<<=1;
	*(speed+3) += Factor * (mask & 0x80 - mask & 0x08); 
}


