#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include "usart_scan.h"


typedef struct device_buf
{
	uint16_t cmd;
	uint16_t head;
	uint16_t tail;
	uint16_t revbuf[4096];
}device;

device device1;
device device2;
device device3;



void Usart2_Init(uint32_t bound)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART1，GPIOA时钟
	
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口1 

}

void bufinit(device dev)
{
	dev.tail = 0;
	dev.cmd = 0;
	dev.head = 0;

}

void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	static u8 state = 0;
	static u8 i = 0;
	static u8 flag = 0;
	static u8 tmp;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		if(state == 0)
		{
				if(Res == 0xaa)
				{
					state = 1;
				}
				else
				{
					state = 0;
				}
		}
		else if(state == 1)	
		{
			flag = Res;
			state = 2;
		}
		else if(state == 2)
		{
			switch (flag)
			{
				case 01:
					if(i == 0)
					{
						device1.cmd = Res;
						i++;
					}else if(i == 1)
					{
						tmp = Res;
						i++;
					}else if(i == 2)
					{
						device1.revbuf[device1.tail] = tmp<<8 | Res;
						device1.tail = (device1.tail+1)%4096;
						state = 0;
						i = 0;
					}
					break;
				case 02:
					if(i == 0)
					{
						device2.cmd = Res;
						i++;
					}else if(i == 1)
					{
						tmp = Res;
						i++;
					}else if(i == 2)
					{
						device2.revbuf[device2.tail] = tmp<<8 | Res;
						device2.tail = (device2.tail+1)%4096;
						state = 0;
						i = 0;
					}
					break;
				case 03:
					if(i == 0)
					{
						device3.cmd = Res;
						i++;
					}else if(i == 1)
					{
						tmp = Res;
						i++;
					}else if(i == 2)
					{
						device3.revbuf[device3.tail] = tmp<<8 | Res;
						device3.tail = (device3.tail+1)%4096;
						state = 0;
						i = 0;
					}
					break;	
				default:
					state = 0;
			}
		}	
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
   } 

} 

