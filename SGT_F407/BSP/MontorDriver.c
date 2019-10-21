#include "MontorDriver.h"

const MontorInstance MONTOR_FRONT_LEFT  = {TIM2,GPIO_Pin_0,GPIO_Pin_1,TIM_SetCompare1};
const MontorInstance MONTOR_FRONT_RIGHT = {TIM3,GPIO_Pin_2,GPIO_Pin_3,TIM_SetCompare2};
const MontorInstance MONTOR_BACK_LEFT   = {TIM4,GPIO_Pin_4,GPIO_Pin_5,TIM_SetCompare3};
const MontorInstance MONTOR_BACK_RIGHT  = {TIM5,GPIO_Pin_6,GPIO_Pin_7,TIM_SetCompare4};

void MontorDriverConfig()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//TIM1 168 000 000hz to 50hz
	TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
	TimeBase_InitStructure.TIM_Prescaler=168;
	TimeBase_InitStructure.TIM_Period=20000;
	TimeBase_InitStructure.TIM_RepetitionCounter = 0;
	TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1,&TimeBase_InitStructure);
	
	TIM_OCInitTypeDef OutputCatch_InitStructure;
	OutputCatch_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	OutputCatch_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	OutputCatch_InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	OutputCatch_InitStructure.TIM_Pulse = 0;
	OutputCatch_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	OutputCatch_InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	OutputCatch_InitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	OutputCatch_InitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1,&OutputCatch_InitStructure);
	TIM_OC2Init(TIM1,&OutputCatch_InitStructure);
	TIM_OC3Init(TIM1,&OutputCatch_InitStructure);
	TIM_OC4Init(TIM1,&OutputCatch_InitStructure);
	TIM_OC1PreloadConfig(TIM1,ENABLE);
	TIM_OC2PreloadConfig(TIM1,ENABLE);
	TIM_OC3PreloadConfig(TIM1,ENABLE);
	TIM_OC4PreloadConfig(TIM1,ENABLE);
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE);
	
	//TIM2 TIM3 TIM4 TIM5 Encoder
	TimeBase_InitStructure.TIM_Period = 65530;
	TimeBase_InitStructure.TIM_Prescaler = 0x00;
	TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV2;
	TIM_TimeBaseInit(TIM2,&TimeBase_InitStructure);
	TIM_TimeBaseInit(TIM3,&TimeBase_InitStructure);
	TIM_TimeBaseInit(TIM4,&TimeBase_InitStructure);
	TIM_TimeBaseInit(TIM5,&TimeBase_InitStructure);
	
	TIM_ICInitTypeDef TIMIC_InintStructure;
	TIM_ICStructInit(&TIMIC_InintStructure);
	TIMIC_InintStructure.TIM_Channel = TIM_Channel_1|TIM_Channel_2;
	TIMIC_InintStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2,&TIMIC_InintStructure);
	TIM_ICInit(TIM3,&TIMIC_InintStructure);
	TIM_ICInit(TIM4,&TIMIC_InintStructure);
	TIM_ICInit(TIM5,&TIMIC_InintStructure);
	
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	TIM_Cmd(TIM5,ENABLE);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_BothEdge);
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_BothEdge);
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_BothEdge);
	TIM_EncoderInterfaceConfig(TIM5,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_BothEdge);
	
	ResetEncoderNum();
}

inline void SetMontorAbsSpeed(unsigned int speed,const MontorInstance* montor)
{
	montor->setFunction(TIM1,speed);//应该在这里添加一个比例系数
}

void SetMontorRotation(bool positive,const MontorInstance* montor)
{
	GPIO_WriteBit(GPIOD,montor->PINA,(BitAction)positive);
	GPIO_WriteBit(GPIOD,montor->PINB,(BitAction)!positive);
}

void SetMontorSpeed(int speed,const MontorInstance* montor)
{
	SetMontorAbsSpeed(speed>0?speed:-speed,montor);
	SetMontorRotation(speed>0,montor);
}

int GetEncoderNum(const MontorInstance* montor)
{
	int count = TIM_GetCounter(montor->TIM);
	if(count<3270)
		return TIM_GetCounter(montor->TIM);
	else
	  return 65530-TIM_GetCounter(montor->TIM);
}

int GetMontorSpeed(const MontorInstance* montor)
{
	int count = TIM_GetCounter(montor->TIM);
	if(count<3270)
		return TIM_GetCounter(montor->TIM)*MONTOR_ENCODER2SPEED_FACTOR;
	else
	  return (TIM_GetCounter(montor->TIM)-65530)*MONTOR_ENCODER2SPEED_FACTOR;
}

void ResetEncoderNum(void)
{
	TIM_SetCounter(TIM2,0);
	TIM_SetCounter(TIM3,0);
	TIM_SetCounter(TIM4,0);
	TIM_SetCounter(TIM5,0);
}
