#include "bsp_motor_init.h"
#include "status.h"



static void BSP_Motor_Init(GPIO_TypeDef* Motor_port,uint16_t	Dir_Pin,uint16_t	Pul_Pin,uint16_t	Ena_Pin,uint32_t Port_Rcc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(Port_Rcc,ENABLE);
	GPIO_InitStructure.GPIO_Pin = Pul_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = Dir_Pin | Ena_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(Motor_port,&GPIO_InitStructure);
	GPIO_SetBits(Motor_port,Ena_Pin);
}

void TIM2_IRQHandler(void)   //TIM3中断
{
	static volatile uint32_t i = 0;

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
			i++;
			if(i ==800-1)
			{
				i = 0;
				MOTOR_SWAP_STOP
			}					
		}
}
void Motor_Swap_Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

}
static void Timer_Init(uint32_t arr1,uint32_t arr2,uint32_t arr3)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	Motor_Swap_Nvic_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 |RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_TimeBaseStructure.TIM_Period = arr1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =7; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_TimeBaseStructure.TIM_Period = arr2;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr3;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1Init(TIM4,	&TIM_OCInitStructure);
	TIM_OC2Init(TIM4,	&TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_SetCompare1(TIM3,1000);  
	TIM_SetCompare2(TIM3,1000);
	TIM_SetCompare3(TIM3,1000);
	TIM_SetCompare1(TIM4,1000); 
	TIM_SetCompare2(TIM4,1000);
	TIM_SetCompare3(TIM2,1000);
	TIM_Cmd(TIM2, ENABLE);  //使能TIM3	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	TIM_Cmd(TIM4, ENABLE);  //使能TIM3
}


void Motor_Init(void)
{
	BSP_Motor_Init(MOTOR1_PORT,0,MOTOR1_PUL_PIN,MOTOR1_ENA_PIN,MOTOR1_PORT_RCC);
	BSP_Motor_Init(MOTOR2_PORT,MOTOR2_DIR_PIN,MOTOR2_PUL_PIN,MOTOR2_ENA_PIN,MOTOR2_PORT_RCC);
	BSP_Motor_Init(MOTOR3_PORT,MOTOR3_DIR_PIN,MOTOR3_PUL_PIN,MOTOR3_ENA_PIN,MOTOR3_PORT_RCC);
	BSP_Motor_Init(MOTOR_SOAK_PORT,MOTOR_SOAK_DIR,MOTOR_SOAK_PUL,MOTOR_SOAK_ENA,MOTOR_SOAK_RCC);
	BSP_Motor_Init(MOTOR_WASH_PORT,MOTOR_WASH_DIR,MOTOR_WASH_PUL,MOTOR_WASH_ENA,MOTOR_WASH_RCC);
	BSP_Motor_Init(MOTOR_SWAP_PORT,0,MOTOR_SWAP_PUL,MOTOR_SWAP_ENA,MOTOR_SWAP_RCC);
	Timer_Init(2810,2810,2810);
}


