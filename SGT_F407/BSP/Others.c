#include "Others.h"
#include "USART.h"

inline void NVICConfig(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

inline void SetSystick()
{
	if(SysTick_Config(168000))
	{
		ErrorMessage("SYSTICK ERROR");
	}
}

void ErrorMessage(char* message)
{
	USART1Send(message);
	while(true);
}

