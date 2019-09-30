#include "Server.h"

//¶æ»úµÄÊµÀý
const ServerInstance SERVER1 = {TIM8,TIM_SetCompare1,500,2000,180};
const ServerInstance SERVER2 = {TIM8,TIM_SetCompare2,500,2000,180};
const ServerInstance SERVER3 = {TIM8,TIM_SetCompare3,500,2000,180};
const ServerInstance SERVER4 = {TIM8,TIM_SetCompare4,500,2000,180};
const ServerInstance SERVER5 = {TIM11,TIM_SetCompare1,500,2000,180};

void ServerConfig(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11|RCC_APB2Periph_TIM8,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//TIM8 TIM11 168 000 000hz to 5Ohz
	TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
	TimeBase_InitStructure.TIM_Prescaler=168;
	TimeBase_InitStructure.TIM_Period=20000;
	TimeBase_InitStructure.TIM_RepetitionCounter = 0;
	TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM8,&TimeBase_InitStructure);
	TIM_TimeBaseInit(TIM11,&TimeBase_InitStructure);
	
	TIM_OCInitTypeDef OutputCatch_InitStructure;
	OutputCatch_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	OutputCatch_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	OutputCatch_InitStructure.TIM_Pulse = 1500;
	OutputCatch_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	OutputCatch_InitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM8,&OutputCatch_InitStructure);
	TIM_OC2Init(TIM8,&OutputCatch_InitStructure);
	TIM_OC3Init(TIM8,&OutputCatch_InitStructure);
	TIM_OC4Init(TIM8,&OutputCatch_InitStructure);
	TIM_OC1Init(TIM11,&OutputCatch_InitStructure);
	TIM_OC1PreloadConfig(TIM8,ENABLE);
	TIM_OC2PreloadConfig(TIM8,ENABLE);
	TIM_OC3PreloadConfig(TIM8,ENABLE);
	TIM_OC4PreloadConfig(TIM8,ENABLE);
	TIM_OC1PreloadConfig(TIM11,ENABLE);
	TIM_ARRPreloadConfig(TIM8,ENABLE);
	TIM_ARRPreloadConfig(TIM11,ENABLE);
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	
	TIM_Cmd(TIM8,ENABLE);
	TIM_Cmd(TIM11,ENABLE);	
}



inline void ServerSetAngle(int angle,const ServerInstance* server)
{
	server->setFunction(server->TIM,server->base+server->PWMRange*angle/server->angleRange);
}
