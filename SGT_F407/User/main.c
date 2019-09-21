/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "USART.h"
#include "Others.h"
#include "LineTrack.h"

void Delay(void);
extern int circle_count;
extern uint32_t systick;

int main()
{
	NVICConfig();
	USART1Config(9600);
	IsUSART1Receive();
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay()
{ 
  for(int i=0;i<3000;i++)for(int i=0;i<300;i++);
}

void block()
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOE, ENABLE);
  
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9 与 GPIOA10 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度 50MHz 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉 
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化 PA9，PA10 
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource3);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0X02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//84 000 000
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
	TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitStructure.TIM_Period = 2000-1;
	TimeBase_InitStructure.TIM_Prescaler = 820-1;//840
	TIM_TimeBaseInit(TIM3,&TimeBase_InitStructure);
	
	TIM_OCInitTypeDef OC_InitStructure;
	OC_InitStructure.TIM_OCMode =TIM_OCMode_PWM1;
	OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	OC_InitStructure.TIM_Pulse = 150;
	TIM_OC4Init(TIM3,&OC_InitStructure);
	
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_CtrlPWMOutputs(TIM3,ENABLE); //*
	TIM_Cmd(TIM3,ENABLE);
	TIM_SetCompare4(TIM3,150);//1500

	//Encoder TIM4 CH1 CH2 PB6 PB7
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6|GPIO_PinSource7,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TimeBase_InitStructure.TIM_Period = 1040;
	TimeBase_InitStructure.TIM_Prescaler = 0x00;
	TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4,&TimeBase_InitStructure);
	
	TIM_ICInitTypeDef TIMIC_InintStructure;
	TIM_ICStructInit(&TIMIC_InintStructure);
	TIMIC_InintStructure.TIM_ICFilter =10;
	TIM_ICInit(TIM4,&TIMIC_InintStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0X01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_SetCounter(TIM4,0);
	TIM_Cmd(TIM4,ENABLE);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_BothEdge);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_CommonInitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_InitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_InitStructure.ADC_Prescaler=ADC_Prescaler_Div4;//ADC 84M <36M
	ADC_CommonInit(&ADC_InitStructure);
	
	ADC_InitTypeDef ADC_InitStructure2;
	ADC_InitStructure2.ADC_Resolution = ADC_Resolution_8b;
	ADC_InitStructure2.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure2.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure2.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure2.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure2.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&ADC_InitStructure2);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_480Cycles);
	ADC_SoftwareStartConv(ADC1);
	
	if(SysTick_Config(168000))
	{
		//时钟初始化出错
	}
	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)){};
	int ans = ADC_GetConversionValue(ADC1);
	char anss[3]={'0','0','0'};
	anss[0]+=ans/100;
	anss[1]+=ans%100/10;
	anss[2]+=ans%10;
	
	USART_SendData(USART1,anss[0]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
	USART_SendData(USART1,anss[1]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
	USART_SendData(USART1,anss[2]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
	
  while (1)
  {
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		USART_SendData(USART1,systick/1000);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
	}
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
	{
	
	}
  }
}
