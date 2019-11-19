#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "BSP.h"

void LED_Blink_Task(void)
{
	while(1)
	{
		BSP_LED_Open();
		vTaskDelay(500);
		BSP_LED_Close();
		vTaskDelay(500);
	}
}

void Serial_Task(void)
{
	while(1)
	{
	  char order[BSP_Serial_MaxOrderLength+1]={0};
		BSP_Serial_Read(order);
		BSP_Serial_SendString(order);
	}
}

TaskHandle_t LED_HANDLE;
TaskHandle_t Serial_HANDLE;


int main()
{
	//初始化硬件设备
	BSP_Modles_Config();
	
	BSP_Serial_SendString("STM32 INIT FINISH");
	
	//创建开始任务
  xTaskCreate((TaskFunction_t )LED_Blink_Task,         //任务函数
                (const char*    )"LED_Blink",          //任务名称
                (uint16_t       )50,        						//任务堆栈大小
                (void*          )NULL,      						//传递给任务函数的参数
                (UBaseType_t    )3,         						//任务优先级
                (TaskHandle_t*  )&LED_HANDLE);   			//任务句柄  
	xTaskCreate((TaskFunction_t )Serial_Task,         //任务函数
                (const char*    )"Serial",          //任务名称
                (uint16_t       )50,        						//任务堆栈大小
                (void*          )NULL,      						//传递给任务函数的参数
                (UBaseType_t    )2,         						//任务优先级
                (TaskHandle_t*  )&Serial_HANDLE);   			//任务句柄  		
	vTaskStartScheduler();
	return 0;
}
