#include "BSP.h"
#include "MotionAnalysis.h"

void BSPConfig(void)
{
	//驱动级初始化
	NVICConfig();
	SystickConfig();
	DelayFunctionConfig();
	USART1Config(9600);
	LCD12864Config();
	//LEDMX7219Config();
	LineTrackConfig();
	MontorDriverConfig();
	ServerConfig();
	MpuConfig();
	//UltrasonicConfig();
	//控制级初始化
	MontionAnalysisConfig();
}

bool BSPTest(void)
{
	return true;
}
