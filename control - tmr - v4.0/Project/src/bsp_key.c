#include "bsp_key.h"
#include "stm32f10x.h"                  // Device header
#include "delay.h"

u8 flag = 0;
void KEY_Init(void)
{ 
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8);
	//PC8
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
}


void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line8)!=RESET)
	{
		delay_ms(10);//����
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0)	 //����KEY0
		{
			flag = !flag;
		}		
	} 
	EXTI_ClearITPendingBit(EXTI_Line8);  //���LINE4�ϵ��жϱ�־λ  
}

