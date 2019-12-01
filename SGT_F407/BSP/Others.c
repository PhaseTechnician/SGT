#include "Others.h"
#include "USART.h"

void (*systemFunction)(void);
bool enableSystemFunctionCycle = false;
int maxCycleNum=1;//最大循环计数
int cycleNumCount;//调用循环次数

inline void NVICConfig(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

unsigned int SystickCount = 0;//10ms单位

inline void SystickConfig(void)
{
	if(SysTick_Config(1680000))//10ms
	{
		ErrorMessage("SYSTICK ERROR");
	}
}

inline unsigned int GetPartTimeS(void)
{
	return SystickCount/100;
}

inline unsigned int GetPartTimeMs(void)
{
	return SystickCount%100*10+SysTick->VAL/168000;
}

inline unsigned int GetPartTimeUs(void)
{
	return SysTick->VAL%168000/168;
}

inline unsigned int GetTotalTimeMs(void)
{
	return SystickCount*10+SysTick->VAL/168000;
}

void SetSystemFunctionCycle(void (*function)(void),int cycleCount)
{
	systemFunction = function;
	maxCycleNum = cycleCount;
}

void EnableSystemFunctionCycle(bool enable)
{
	enableSystemFunctionCycle = enable;
}

void SysTick_Handler(void)
{
	SystickCount++;
	if(enableSystemFunctionCycle)
	{
		if(cycleNumCount >= maxCycleNum)
		{
			systemFunction();
			cycleNumCount = 0;
		}
		else 
		{
			cycleNumCount++;
		}
	}
}

void DelayFunctionConfig(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	//TIM6 84 000 000 hz
	TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
	TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitStructure.TIM_Prescaler = 84;
	TimeBase_InitStructure.TIM_Period=65535;
	TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM6,&TimeBase_InitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

bool ClockDelayOpen = false;

void Delay(int16_t us)
{
  	ClockDelayOpen=true;
	TIM_SetCounter(TIM6,65535-us);
	TIM_Cmd(TIM6,ENABLE);
	while(ClockDelayOpen);
	TIM_Cmd(TIM6,DISABLE);
}

void DelayMs(unsigned int ms)
{
	for(int i=0;i<ms;i++)
	Delay(1000);
}

void DelayS(unsigned int s)
{
	for(int i=0;i<s*1000;i++)
	Delay(1000);
}

void TIM6_DAC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET)
	{
		ClockDelayOpen = false;
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}
}

void ErrorMessage(char* message)
{
	USART1Send(message);
	while(true);
}

