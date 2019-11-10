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
	
	//������ʼ����
  xTaskCreate((TaskFunction_t )LED_Blink_Task,            //������
                (const char*    )"LED_Blink",          //��������
                (uint16_t       )50,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )1,       //�������ȼ�
                (TaskHandle_t*  )&LED_HANDLE);   //������    
	vTaskStartScheduler();
	return 0;
}
