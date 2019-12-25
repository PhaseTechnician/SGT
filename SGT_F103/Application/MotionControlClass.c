#include "MotionControlClass.h"

#include "BSP.h"
#include "PIDController.h"
#include "MotionAnalysis.h"

#include "FreeRTOS.h"
#include "task.h"

#include "AHRS.h"
#include "Application.h"

PIDInstance PID1, PID2, PID3, PID4;

void EncoderReadTask(void)
{
	MontorSpeed speedInformation;
	TickType_t xLastWakeTime;
	while (1)
	{
		//从编码器获取数据
		speedInformation.speed1 = BSP_Encoder_GetCode(TIM2);
		speedInformation.speed2 = BSP_Encoder_GetCode(TIM3);
		speedInformation.speed3 = BSP_Encoder_GetCode(TIM4);
		speedInformation.speed4 = BSP_Encoder_GetCode(TIM5);
		//进行处理,重新映射范围实现编码器一致性
		speedInformation.speed1 = speedInformation.speed1 * 1;
		speedInformation.speed2 = speedInformation.speed2 * 1;
		speedInformation.speed3 = speedInformation.speed3 * 1;
		speedInformation.speed4 = speedInformation.speed4 * 1;
		//发送到队列
		xQueueOverwrite(MontorSpeedHandle, &speedInformation);
		vTaskDelayUntil(&xLastWakeTime, 100);
	}
}

void AttitudeSolutionTask(void)
{
	static TickType_t tick;
	taskENTER_CRITICAL();
	if (BSP_MPU_CheckOnLine())
	{
		BSP_Serial_SendString("MPU9250 Online\n");
		BSP_MPU_WakeUp();
		vTaskDelay(100);
		BSP_MPU_RegesterConfig();
		vTaskDelay(100);
	}
	else
	{
		taskEXIT_CRITICAL();
		BSP_Serial_SendString("MPU9250 Offline,Please Check Connected\n");
		while (1)
		{
			BSP_MPU_CheckOnLine();
			vTaskDelay(100);
		}
		//vTaskSuspend(AttitudeSolutionTaskHandler);
	}
	taskEXIT_CRITICAL();
	while (1)
	{
		//从IMU获取原始姿态数据
		taskENTER_CRITICAL();
		Vector3 acc = {BSP_MPU_ReadACCX(), BSP_MPU_ReadACCY(), BSP_MPU_ReadACCZ()};
		Vector3 omg = {BSP_MPU_ReadOMGX(), BSP_MPU_ReadOMGY(), BSP_MPU_ReadOMGZ()};
		//Vector3 mag = {BSP_MPU_ReadMAGX(), BSP_MPU_ReadMAGY(), BSP_MPU_ReadMAGZ()};
		taskEXIT_CRITICAL();

		//解算当前姿态
		EulerAngle angle = GetInitalEularAngle(acc);

		BSP_Serial_SendInt((int)(angle.pitch * 57.0f));
		BSP_Serial_SendChar(' ');
		BSP_Serial_SendInt((int)(angle.roll * 57.0f));
		BSP_Serial_SendChar('\n');

		//发送到队列
		xQueueOverwrite(AttitudeHandle, &angle);
		vTaskDelayUntil(&tick, 10);
	}
}

void MotorSpeedControlTask(void)
{
	MontorSpeed tragetSpeedInformation;
	MontorSpeed realSpeedInformation;
	InitOnePIDInstance(&PID1, 0, 1, 0, 0);
	InitOnePIDInstance(&PID2, 0, 1, 0, 0);
	InitOnePIDInstance(&PID3, 0, 1, 0, 0);
	InitOnePIDInstance(&PID4, 0, 1, 0, 0);
	while (1)
	{
		vTaskDelay(500);
		//从队列读取速度信息
		xQueueReceive(MontorTragetSpeedHandle, &tragetSpeedInformation, 0);
		//从队列读取目标速度
		xQueueReceive(MontorSpeedHandle, &realSpeedInformation, portMAX_DELAY);
		//计算当前控制量
		//使用PID控制器
		realSpeedInformation.speed1 = FinishOnePIDStep(&PID1, realSpeedInformation.speed1);
		realSpeedInformation.speed2 = FinishOnePIDStep(&PID2, realSpeedInformation.speed2);
		realSpeedInformation.speed3 = FinishOnePIDStep(&PID3, realSpeedInformation.speed3);
		realSpeedInformation.speed4 = FinishOnePIDStep(&PID4, realSpeedInformation.speed4);
		//输出控制量
		BSP_MontorDriver_3Pin_SetOutPut(realSpeedInformation.speed1, MontorFL);
		BSP_MontorDriver_3Pin_SetOutPut(realSpeedInformation.speed2, MontorFR);
		BSP_MontorDriver_3Pin_SetOutPut(realSpeedInformation.speed3, MontorBL);
		BSP_MontorDriver_3Pin_SetOutPut(realSpeedInformation.speed4, MontorBR);
	}
}

void MotionControlTask(void)
{
	static MotionControlOrder ControlOrder;
	static EulerAngle angle;
	static TickType_t tick;
	while (1)
	{
		bool change = false;
		//从队列获取姿态修改指令【非阻塞】
		if (xQueueReceive(MotionControlOrderHandle, &ControlOrder, 0))
		{
			change = true;
		}
		//从队列获取IMU姿态信息
		if (xQueueReceive(AttitudeHandle, &angle, 0))
		{
			change = true;
		}
		if (change)
		{
			float speed[4] = {0.0f};
			//解算合适的四轮目标速度
			switch(ControlOrder.motion)
			{
				case MotionType_Translate_Forward :
					ApplyMaskWithFactor(speed,WHEEL_MASK_FORWARD,ControlOrder.value);
					break;
				case MotionType_Translate_Backward :
					ApplyMaskWithFactor(speed,WHEEL_MASK_BACKWARD,-ControlOrder.value);
					break;
				default:
					break;
			}
			if(angle.yaw)
			{
				
			}
			//发送到队列
			xQueueOverwrite(MontorTragetSpeedHandle, &speed);
		}
		vTaskDelayUntil(&tick, 50);
	}
}
