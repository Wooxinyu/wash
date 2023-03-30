#ifndef BSP_MOTOR_INIT__
#define BSP_MOTOR_INIT__
#include "stm32f10x.h"

#define MOTOR1_PORT  GPIOA


#define MOTOR1_ENA_PIN   GPIO_Pin_4
#define MOTOR1_PUL_PIN   GPIO_Pin_6
#define MOTOR1_PORT      GPIOA
#define MOTOR1_TIM_RCC   RCC_APB1Periph_TIM3
#define MOTOR1_PORT_RCC  RCC_APB2Periph_GPIOA


#define MOTOR2_ENA_PIN   GPIO_Pin_5
#define MOTOR2_PUL_PIN	 GPIO_Pin_7
#define MOTOR2_DIR_PIN	 GPIO_Pin_9
#define MOTOR2_PORT      GPIOA
#define MOTOR2_TIM_RCC   RCC_APB1Periph_TIM3
#define MOTOR2_PORT_RCC  RCC_APB2Periph_GPIOA

#define MOTOR3_ENA_PIN   GPIO_Pin_10
#define MOTOR3_PUL_PIN   GPIO_Pin_0
#define MOTOR3_DIR_PIN	 GPIO_Pin_12
#define MOTOR3_PORT      GPIOB
#define MOTOR3_PORT_RCC  RCC_APB2Periph_GPIOB
#define MOTOR3_TIM_RCC   RCC_APB1Periph_TIM3
 

#define MOTOR_WASH_ENA  GPIO_Pin_13
#define MOTOR_WASH_PUL	GPIO_Pin_6
#define MOTOR_WASH_DIR	GPIO_Pin_8
#define MOTOR_WASH_PORT	GPIOB
#define MOTOR_WASH_RCC	RCC_APB2Periph_GPIOB

#define MOTOR_SOAK_ENA	GPIO_Pin_5
#define MOTOR_SOAK_PUL	GPIO_Pin_7
#define MOTOR_SOAK_DIR	GPIO_Pin_9
#define MOTOR_SOAK_PORT	GPIOB
#define MOTOR_SOAK_RCC	RCC_APB2Periph_GPIOB

#define MOTOR_SWAP_ENA	GPIO_Pin_3
#define MOTOR_SWAP_PUL	GPIO_Pin_2
#define MOTOR_SWAP_PORT	GPIOA	
#define MOTOR_SWAP_RCC	RCC_APB2Periph_GPIOA

void Motor_Init(void);
void Timer_Init(uint32_t arr1,uint32_t	arr2,uint32_t arr3);

#endif
