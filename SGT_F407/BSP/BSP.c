#include "BSP.h"

void BSPConfig(void)
{
	NVICConfig();
	SystickConfig();
	DelayFunctionConfig();
	USART1Config(9600);
	LCD12864Config();
	LineTrackConfig();
	MontorDriverConfig();
	ServerConfig();
	MpuConfig();
	UltrasonicConfig();
}

bool BSPTest(void)
{
	return true;
}
