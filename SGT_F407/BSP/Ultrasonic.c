#include "Ultrasonic.h"

unsigned char stateMachineLable = 0;//0->1->...->7
bool allDetectedFinish = false;

bool isFinish = true;//记录是否完成一次计量
bool isStart = false;//上升沿之后true，超时或者下降沿为false
uint16_t echoLength = 0;

UltrasoniceInstance ULT1 = {GPIOE,GPIO_Pin_3,0};
UltrasoniceInstance ULT2 = {GPIOE,GPIO_Pin_4,0};
UltrasoniceInstance ULT3 = {GPIOE,GPIO_Pin_5,0};
UltrasoniceInstance ULT4 = {GPIOE,GPIO_Pin_6,0};

void UltrasonicConfig(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12|RCC_APB1Periph_TIM13|RCC_APB1Periph_TIM14,ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM13);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
	TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitStructure.TIM_Prescaler = 42-1;
	TimeBase_InitStructure.TIM_Period = 40000-1; //20 ms 自动退出计时
	TimeBase_InitStructure.TIM_RepetitionCounter = 0;
	TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM13,&TimeBase_InitStructure);
	
	TIM_ICInitTypeDef TimeIC_InitStructure;
	TimeIC_InitStructure.TIM_Channel = TIM_Channel_1|TIM_Channel_2;
	TimeIC_InitStructure.TIM_ICFilter = 0x00;
	TimeIC_InitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TimeIC_InitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TimeIC_InitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	//TIM_ICInit(TIM12,&TimeIC_InitStructure);
	TimeIC_InitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInit(TIM13,&TimeIC_InitStructure);
	//TIM_ICInit(TIM14,&TimeIC_InitStructure);
	
	//TIM_ITConfig(TIM12,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2,ENABLE);
	TIM_ITConfig(TIM13,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	//TIM_ITConfig(TIM14,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	//NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn;
	//NVIC_Init(&NVIC_InitStructure);
	
	//TIM_Cmd(TIM12,ENABLE);
	TIM_Cmd(TIM13,ENABLE);
	//TIM_Cmd(TIM14,ENABLE);
}

void StartOnceDetecte(UltrasoniceInstance* instance)
{
	GPIO_SetBits(instance->TIM,instance->pin);
	Delay(20);
	GPIO_ResetBits(instance->TIM,instance->pin);
	isFinish = false;
}

void UltrasonicOnStep(void)
{
	switch(stateMachineLable)
	{
		case 0:
			//StratOnceDetecte();
			break;
		case 1:
			
			break;
	}
}


int GetDistance(UltrasoniceInstance* instance)
{
	while(!isFinish);
	return echoLength;
}

inline int GetCM(int count)
{
	return count*17000/2000000;
}

void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM13,TIM_IT_CC1)!=RESET)
	{
		if(isStart)
		{
			echoLength = TIM_GetCapture1(TIM13);
			isStart = false;
			isFinish = true;
			TIM_OC1PolarityConfig(TIM13,TIM_ICPolarity_Rising);
		}
		else
		{
			TIM_SetCounter(TIM13,0);
			isStart = true;
			TIM_OC1PolarityConfig(TIM13,TIM_ICPolarity_Falling);
		}
		TIM_ClearITPendingBit(TIM13,TIM_IT_CC1);
	}
	else if(TIM_GetITStatus(TIM13,TIM_IT_Update)!=RESET)
	{
		if(isStart)
		{
			TIM_SetCounter(TIM13,0);
			isStart = false;
			isFinish = true;
			echoLength = 40000;
			TIM_OC1PolarityConfig(TIM13,TIM_ICPolarity_Rising);
		}
		TIM_ClearITPendingBit(TIM13,TIM_IT_Update);
	}
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
	
}

void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	
}
