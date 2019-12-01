#include "BSP.h"

void BSP_Modles_Config(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	BSP_Delay_Config();
	BSP_LED_Config();
	BSP_Serial_Config(9600);
	BSP_MPU_Config();
}

bool BSP_Modles_Test(void)
{
	return true;
}
