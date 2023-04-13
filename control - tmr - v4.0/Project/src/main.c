#include "stm32f10x.h"
#include "delay.h"
#include "bsp_key.h"
#include "bsp_motor_init.h"
#include "status.h"
extern u8 flag; 
int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	Motor_Init();
	KEY_Init();
	while(1)
	{

	}
	
}

