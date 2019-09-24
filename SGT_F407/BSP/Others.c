#include "Others.h"
#include "USART.h"

inline void NVICConfig(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

inline void SystickConfig(void)
{
	if(SysTick_Config(168000))
	{
		ErrorMessage("SYSTICK ERROR");
	}
}

void SysTick_Handler(void)
{

}

void ErrorMessage(char* message)
{
	USART1Send(message);
	while(true);
}


