#include "BSP.h"
#include "MotionAnalysis.h"

void BSPConfig(void)
{
	//��������ʼ��
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
	//���Ƽ���ʼ��
	MontionAnalysisConfig();
}

bool BSPTest(void)
{
	return true;
}
