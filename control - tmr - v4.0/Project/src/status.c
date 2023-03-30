#include "status.h"
#include "delay.h"
#include "bsp_motor_init.h"
extern u8 state;
void status1(void)
{
	MOTOR1_RUN_ONE
	delay_ms(1000);
	MOTOR2_RUN_ONE
	state = 2;
}

void status2(void)
{
	MOTOR_WASH_STOP
	MOTOR2_RUN_ONE
	MOTOR_WASH_DOWN
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	MOTOR_WASH_UP
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	MOTOR2_RUN_ONE;
	MOTOR_WASH_DOWN
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	MOTOR_WASH_UP
	MOTOR2_RUN_ONE
	state = 3;
}


void status3(void)
{
	uint32_t i = 20*60*60-1;
	MOTOR3_RUN_ON
	MOTOR_SWAP_RUN
	delay_ms(250);
	MOTOR_SWAP_STOP
	delay_ms(750);
	MOTOR_SOAK_DOWN
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
//	do
//	{
//		delay_ms(1000);
//	}while(i--);
	MOTOR_SOAK_UP
	delay_ms(75);

	MOTOR_SWAP_RUN
	delay_ms(250);
	MOTOR_SWAP_STOP
	delay_ms(50);
	MOTOR3_RUN_BACK
	delay_ms(1000);
	MOTOR_WASH_DOWN
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	MOTOR_WASH_UP
	state = 4;
 }

void	status4(void)
{
	MOTOR_WASH_DOWN
	delay_ms(1000);
	MOTOR_WASH_UP
	delay_ms(1000);
	MOTOR2_RUN_ONE
	MOTOR3_RUN_ON

}

