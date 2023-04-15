#include "motor_control.h"
#include "stm32f10x.h"
#include "bsp_motor_init.h"

void TIM2_Control_Decision(int index)
{
	
	switch (index)
			{
				case 0:
					MOTOR1_STOP			
					MOTOR_SWAP_RUN
					break;
				case 1:
					MOTOR_SWAP_STOP
					MOTOR_WASH_DIR_DOWN
					MOTOR_WASH_RUN
					break;
				case 2:
					WASH_ON
					MOTOR_WASH_STOP
					break;
				case 3:
					WASH_OFF
					MOTOR_WASH_DIR_UP
					MOTOR_WASH_RUN
					break;
				case 4:
					MOTOR_WASH_STOP
					MOTOR1_RUN
					break;
				case 5:
					MOTOR1_STOP
					MOTOR_WASH_DIR_DOWN
					MOTOR_WASH_RUN
					break;
				case 6:
					MOTOR_WASH_STOP
					break;
				case 7:
					MOTOR_WASH_DIR_UP
					MOTOR_WASH_RUN
					break;	
				case 8:
					MOTOR_WASH_STOP
					MOTOR1_RUN
					break;				
				default :
					TIM_Cmd(TIM3, DISABLE);  //Ê¹ÄÜTIM3
			}
}

