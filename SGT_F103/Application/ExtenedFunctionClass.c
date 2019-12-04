#include "ExtenedFunctionClass.h"
#include "BSP.h"
#include "FreeRTOS.h"
#include "task.h"

void BeepNoisyTask(void)
{
	while(1)
	{
	//获取蜂鸣器信号控制量
	
	vTaskDelay(500);
	}
}

void LEDControlsTask(void)
{
	while(1)
	{
	//获取LED信号控制量
	
	//做出效果
	
		BSP_LED_Open();
		vTaskDelay(500);
		BSP_LED_Close();
		vTaskDelay(500);
	}
}
