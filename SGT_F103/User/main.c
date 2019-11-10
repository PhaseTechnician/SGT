#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

void LED_Blink_Task(void)
{
	while(1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		vTaskDelay(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		vTaskDelay(500);
	}
}

TaskHandle_t LED_HANDLE;

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_Structure;
	GPIO_Structure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_Structure.GPIO_Pin=GPIO_Pin_13;
	GPIO_Structure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_Structure);
	
	//创建开始任务
  xTaskCreate((TaskFunction_t )LED_Blink_Task,            //任务函数
                (const char*    )"LED_Blink",          //任务名称
                (uint16_t       )50,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )1,       //任务优先级
                (TaskHandle_t*  )&LED_HANDLE);   //任务句柄    
	vTaskStartScheduler();
	return 0;
}
