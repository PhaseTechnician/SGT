#include "ExtenedFunctionClass.h"
#include "BSP.h"
#include "FreeRTOS.h"
#include "task.h"

void BeepNoisyTask(void)
{
	while(1)
	{
	//��ȡ�������źſ�����
	
	vTaskDelay(500);
	}
}

void LEDControlsTask(void)
{
	while(1)
	{
	//��ȡLED�źſ�����
	
	//����Ч��
	
		BSP_LED_Open();
		vTaskDelay(500);
		BSP_LED_Close();
		vTaskDelay(500);
	}
}
