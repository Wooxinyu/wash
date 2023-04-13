#ifndef STATUS_H__
#define STATUS_H__



#define MOTOR1_RUN   digitalLo(MOTOR1_PORT, MOTOR1_ENA_PIN)
#define MOTOR1_STOP  digitalHi(MOTOR1_PORT, MOTOR1_ENA_PIN)

#define MOTOR2_RUN    digitalLo(MOTOR2_PORT,MOTOR2_ENA_PIN)
#define MOTOR2_STOP   digitalHi(MOTOR2_PORT,MOTOR2_ENA_PIN)

#define MOTOR3_RUN    digitalLo(MOTOR3_PORT,MOTOR3_ENA_PIN)


#define MOTOR_WASH_RUN	digitalLo(MOTOR_WASH_PORT,MOTOR_WASH_ENA)
#define MOTOR_WASH_STOP	digitalHi(MOTOR_WASH_PORT,MOTOR_WASH_ENA)
#define MOTOR_WASH_DIR_UP	digitalHi(MOTOR_WASH_PORT,MOTOR_WASH_DIR)
#define MOTOR_WASH_DIR_DOWN	digitalLo(MOTOR_WASH_PORT,MOTOR_WASH_DIR)



#define MOTOR_SWAP_STOP {	digitalHi(MOTOR_SWAP_PORT,MOTOR_SWAP_ENA)										\
												}

#define MOTOR_SWAP_RUN 		{	digitalLo(MOTOR_SWAP_PORT,MOTOR_SWAP_ENA)										\
													}
#define MOTOR1_RUN_ONE		{	MOTOR1_RUN			\
														delay_ms(1000);	\
														MOTOR1_STOP			\
														delay_ms(500);	\
													}

#define MOTOR2_RUN_ONE		{	while(flag); 		\
														MOTOR2_RUN			\
														delay_ms(1000);	\
														MOTOR2_STOP			\
														delay_ms(500); 	\
													}
#define MOTOR2_RUN_HALF		{	MOTOR2_RUN			\
														delay_ms(500);	\
														MOTOR2_STOP			\
														delaay_ms(50);	\
													}



#define MOTOR_WASH_DOWN			{	while(flag); 		\
															MOTOR_WASH_DIR_DOWN	\
															MOTOR_WASH_RUN			\
															delay_ms(1000);			\
															MOTOR_WASH_STOP			\
															delay_ms(500);			\
														}

#define MOTOR_WASH_UP			{	while(flag); 		\
														MOTOR_WASH_DIR_UP	\
														MOTOR_WASH_RUN		\
														delay_ms(1000);		\
														MOTOR_WASH_STOP		\
														delay_ms(500);		\
													}

#define  WASH_ON				{	digitalHi(WASH_RELAY_PORT, WASH_RELAY_PIN) }

#define	 WASH_OFF				{ digitalLo(WASH_RELAY_PORT, WASH_RELAY_PIN)	}

#define OVEN_ON					{	digitalHi(OVEN_RELAY_PORT, OVEN_RELAY_PIN) \
												}

#define OVEN_OFF				{	digitalLo(OVEN_RELAY_PORT, OVEN_RELAY_PIN)	\
												}

/********************************************/
/****************GPIOSET*********************/
/**********************************************/
#define digitalHi(p,i) 			{p->BSRR=i;}
#define digitalLo(p,i) 			{p->BRR=i;}
#define digitalToggle(p,i) 	{p->ODR ^= i;}

void status1(void);
void status2(void);
void status3(void);



#endif

