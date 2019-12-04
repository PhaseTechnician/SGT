#include "MotionControlClass.h"

#include "BSP.h"
#include "FreeRTOS.h"
#include "task.h"

void EncoderReadTask(void)
{
	while(1)
	{
	//�ӱ�������ȡ����
	BSP_Encoder_GetCode(TIM2);
	BSP_Encoder_GetCode(TIM3);
	BSP_Encoder_GetCode(TIM4);
	BSP_Encoder_GetCode(TIM5);
	
	//���͵�����
	
	}
}

void AttitudeSolutionTask(void)
{
	while(1)
	{
	if(BSP_MPU_CheckOnLine())
	{
		BSP_Serial_SendString("MPU SUCCESS");
		BSP_MPU_WakeUp();
		vTaskDelay(100);
		BSP_MPU_RegesterConfig();
		vTaskDelay(100);
	}
	else
	{
		BSP_Serial_SendString("MPU  FAIL");
	}

	//��IMU��ȡԭʼ��̬����
	BSP_MPU_ReadACCX();
	BSP_MPU_ReadACCY();
	BSP_MPU_ReadACCZ();
	BSP_MPU_ReadOMGX();
	BSP_MPU_ReadOMGY();
	BSP_MPU_ReadOMGZ();
	//..
	
	//���㵱ǰ��̬
	
	//���͵�����
	
	}
}

void MotorSpeedControlTask(void)
{
	while(1)
	{
	vTaskDelay(500);
	//�Ӷ��ж�ȡ�ٶ���Ϣ
	
	//�Ӷ��ж�ȡĿ���ٶ�
	
	//���㵱ǰ������
	
	//���������
	}
}

void MotionControlTask(void)
{
	while(1)
	{
	vTaskDelay(500);
	//�Ӷ��л�ȡ��̬�޸�ָ���������
	
	//�Ӷ��л�ȡIMU��̬��Ϣ
	
	//������ʵ�����Ŀ���ٶ�
	
	//���͵�����
	}
}
