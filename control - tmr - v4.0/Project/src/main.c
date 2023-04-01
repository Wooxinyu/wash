#include "stm32f10x.h"
#include "delay.h"
#include "bsp_key.h"
#include "bsp_motor_init.h"
#include "status.h"
u8 state = 0;
extern u8 flag; 
int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	Motor_Init();
	KEY_Init();
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	while(1)
	{
		if(!flag)
		MOTOR2_STOP
		else
			MOTOR2_RUN
	}
	
}

