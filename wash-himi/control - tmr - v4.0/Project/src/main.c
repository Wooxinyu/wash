#include "stm32f10x.h"
#include "delay.h"
#include "bsp_key.h"
#include "bsp_motor_init.h"
#include "motor_control.h"
#include "usart.h"
#include "stdio.h"

#define FRAMELENGTH 6


extern u8 flag; 
int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	Motor_Init();
	KEY_Init();
	uart_init(115200);
	delay_ms(1500);
	printf("\0x00\0xff\0xff\0xff\r\n");
	u16 t;  
	u16 len;
	while(1)
	{
		if(USART_RX_BUF[0]== 0X55)
		{
			if(USART_RX_BUF[1] == 0x05)
			{
				//MOTOR1_RUN
				TIM_Cmd(TIM3,ENABLE);
				digitalLo(MOTOR1_PORT, MOTOR1_ENA_PIN)
			}else if(USART_RX_BUF[1] == 0x03)
			{
//				MOTOR1_STOP
//				MOTOR_WASH_STOP
//				MOTOR_SWAP_STOP
				TIM_Cmd(TIM3,DISABLE);
			}
		USART_RX_BUF[1] = 0X00;		
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			USART_RX_STA=0;
		}
	}
	else
	{
				clearBuff();
	}

		
	}
}
	


