#ifndef USART_H__
#define	USART_H__ 

#define USART_REC_LEN  			2 	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
void uart_init(u32 bound);
uint8_t Usart_GetRxFlag(void);
void Clear_Buf(void);
#endif


