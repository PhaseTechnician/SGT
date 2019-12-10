#include "MotionControlClass.h"

#include "BSP.h"
#include "PIDController.h"

#include "FreeRTOS.h"
#include "task.h"

#include "Application.h"

PIDInstance PID1,PID2,PID3,PID4;

void EncoderReadTask(void)
{
	MontorSpeed speedInformation;
	while(1)
	{
	//�ӱ�������ȡ����
	speedInformation.speed1 = BSP_Encoder_GetCode(TIM2);
	speedInformation.speed2 = BSP_Encoder_GetCode(TIM3);
	speedInformation.speed3 = BSP_Encoder_GetCode(TIM4);
	speedInformation.speed4 = BSP_Encoder_GetCode(TIM5);
	//���д���
	
	//���͵�����
	xQueueOverwrite(MontorSpeedHandle,&speedInformation);
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
	MontorSpeed tragetSpeedInformation;
	MontorSpeed realSpeedInformation;
	InitOnePIDInstance(&PID1,0,1,0,0);
	InitOnePIDInstance(&PID2,0,1,0,0);
	InitOnePIDInstance(&PID3,0,1,0,0);
	InitOnePIDInstance(&PID4,0,1,0,0);
	while(1)
	{
	vTaskDelay(500);
	//�Ӷ��ж�ȡ�ٶ���Ϣ
	xQueueReceive(MontorTragetSpeedHandle,&tragetSpeedInformation,0);
	//�Ӷ��ж�ȡĿ���ٶ�
	xQueueReceive(MontorSpeedHandle,&realSpeedInformation,portMAX_DELAY);
	//���㵱ǰ������
		//ʹ��PID������
		realSpeedInformation.speed1=FinishOnePIDStep(&PID1,realSpeedInformation.speed1);
		realSpeedInformation.speed2=FinishOnePIDStep(&PID2,realSpeedInformation.speed2);
		realSpeedInformation.speed3=FinishOnePIDStep(&PID3,realSpeedInformation.speed3);
		realSpeedInformation.speed4=FinishOnePIDStep(&PID4,realSpeedInformation.speed4);
	//���������
	//BSP_MontorDriver_3Pin_SetOutPut();
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
