#include "BSP.h"

void BSPConfig(void)
{
	NVICConfig();
	SystickConfig();
	USART1Config(9600);
	LineTrackConfig();
	MontorDriverConfig();
	ServerConfig();
	LedConfig();
	MpuConfig();
	UltrasonicConfig();
}

bool BSPTest(void)
{
	return true;
}
