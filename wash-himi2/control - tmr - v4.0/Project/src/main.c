#include "stm32f10x.h"
#include "delay.h"
#include "bsp_key.h"
#include "bsp_motor_init.h"
#include "motor_control.h"
#include "usart.h"
#include "stdio.h"
#include "usart_scan.h"
#define FRAMELENGTH 6


extern u8 flag; 
int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	Motor_Init();
	KEY_Init();
	uart_init(115200);
	Usart2_Init(115200);
	delay_ms(1500);
	printf("初始化成功\r\n");
	u16 t;  
	u16 len;
	while(1)
	{
		if(Usart_GetRxFlag())
		{
			if(USART_RX_BUF[0] == 0X05)
			{
				TIM_Cmd(TIM3,ENABLE);
				digitalLo(MOTOR1_PORT, MOTOR1_ENA_PIN)
			}
			if(USART_RX_BUF[0] == 0X03)
			{
				TIM_Cmd(TIM3,DISABLE);
			}
//		}
	for(len = 0; len < 2; len++)
	{
		USART_SendData(USART1,USART_RX_BUF[len]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}}
//	Clear_Buf();
		
	}
}
	


