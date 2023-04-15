#ifndef MOTOR_CONTROL_H__
#define MOTOR_CONTROL_H__



#define MOTOR1_RUN   {digitalLo(MOTOR1_PORT, MOTOR1_ENA_PIN)  \
											TIM_CCxCmd(TIM3,TIM_Channel_1 ,ENABLE);}
#define MOTOR1_STOP  {digitalHi(MOTOR1_PORT, MOTOR1_ENA_PIN)	\
											TIM_CCxCmd(TIM3,TIM_Channel_1,DISABLE);}
#define MOTOR2_RUN    digitalLo(MOTOR2_PORT,MOTOR2_ENA_PIN)
#define MOTOR2_STOP   digitalHi(MOTOR2_PORT,MOTOR2_ENA_PIN)


#define MOTOR_WASH_RUN	{digitalLo(MOTOR_WASH_PORT,MOTOR_WASH_ENA)	\
												TIM_CCxCmd(TIM3,TIM_Channel_3 ,ENABLE);	}
#define MOTOR_WASH_STOP	{digitalHi(MOTOR_WASH_PORT,MOTOR_WASH_ENA)	\
													TIM_CCxCmd(TIM3,TIM_Channel_3 ,DISABLE);}
#define MOTOR_WASH_DIR_UP	digitalHi(MOTOR_WASH_PORT,MOTOR_WASH_DIR)
#define MOTOR_WASH_DIR_DOWN	digitalLo(MOTOR_WASH_PORT,MOTOR_WASH_DIR)



#define MOTOR_SWAP_STOP {	digitalHi(MOTOR_SWAP_PORT,MOTOR_SWAP_ENA)		\
													TIM_CCxCmd(TIM3,TIM_Channel_4 ,DISABLE);}

#define MOTOR_SWAP_RUN 		{	digitalLo(MOTOR_SWAP_PORT,MOTOR_SWAP_ENA)	\
														TIM_CCxCmd(TIM3,TIM_Channel_4 ,ENABLE);}


#define  WASH_ON				{	digitalHi(WASH_RELAY_PORT, WASH_RELAY_PIN) }

#define	 WASH_OFF				{ digitalLo(WASH_RELAY_PORT, WASH_RELAY_PIN)	}

#define OVEN_ON					{	digitalHi(OVEN_RELAY_PORT, OVEN_RELAY_PIN)	 }

#define OVEN_OFF				{	digitalLo(OVEN_RELAY_PORT, OVEN_RELAY_PIN)	}

/********************************************/
/****************GPIOSET*********************/
/**********************************************/
#define digitalHi(p,i) 			{p->BSRR=i;}
#define digitalLo(p,i) 			{p->BRR=i;}
#define digitalToggle(p,i) 	{p->ODR ^= i;}


void TIM2_Control_Decision(int index);



#endif

