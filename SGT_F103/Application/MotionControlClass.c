#include "MotionControlClass.h"

#include "BSP.h"
#include "FreeRTOS.h"
#include "task.h"

void EncoderReadTask(void)
{
	while(1)
	{
	//从编码器获取数据
	BSP_Encoder_GetCode(TIM2);
	BSP_Encoder_GetCode(TIM3);
	BSP_Encoder_GetCode(TIM4);
	BSP_Encoder_GetCode(TIM5);
	
	//发送到队列
	
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

	//从IMU获取原始姿态数据
	BSP_MPU_ReadACCX();
	BSP_MPU_ReadACCY();
	BSP_MPU_ReadACCZ();
	BSP_MPU_ReadOMGX();
	BSP_MPU_ReadOMGY();
	BSP_MPU_ReadOMGZ();
	//..
	
	//解算当前姿态
	
	//发送到队列
	
	}
}

void MotorSpeedControlTask(void)
{
	while(1)
	{
	vTaskDelay(500);
	//从队列读取速度信息
	
	//从队列读取目标速度
	
	//计算当前控制量
	
	//输出控制量
	}
}

void MotionControlTask(void)
{
	while(1)
	{
	vTaskDelay(500);
	//从队列获取姿态修改指令【非阻塞】
	
	//从队列获取IMU姿态信息
	
	//解算合适的四轮目标速度
	
	//发送到队列
	}
}
