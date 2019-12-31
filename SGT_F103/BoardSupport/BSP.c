#include "BSP.h"

void BSP_Modles_Config(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	BSP_Delay_Config();
	BSP_LED_Config();
	BSP_Beep_Config();
	BSP_Serial_Config(9600);
	BSP_KeyBoard_Config();
	BSP_LCD12864_Config();
	BSP_MontorDriver_3Pin_Config();
	BSP_Encoder_Config();
	BSP_MPU_Config();//ƒ≥¥Œ≤‚ ‘÷–MPU”ÎEncoder≥ÂÕª
	BSP_SerialIO_Config();
}

bool BSP_Modles_Test(void)
{
	return true;
}
