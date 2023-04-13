#include "bsp_motor_control.h"
#include "bsp_motor_init.h"
#include "delay.h"
// PA7 TIM3CH2
/*
加速中返回0
加速完毕返回1

*/

motor motor_init(u16 min_delay,u16 step)
{
	motor m;
	m.State = FASTING;
	m.dir = CW;
	m.max_delay = MAX_DELAY;
	m.min_delay = min_delay;
	m.cur_delay = MAX_DELAY;
	m.step = step;
	m.next_delay = min_delay;
	return m;
}

static void motor_faster(motor *m)
{
		if((*m).cur_delay > (*m).min_delay){
			(*m).cur_delay-=((*m).max_delay-(*m).min_delay)/24;
			TIM_SetAutoreload(TIM3,(*m).cur_delay); 
			TIM_SetCompare2(TIM3,((*m).cur_delay)/2);
			(*m).State = FASTING;
		}
		else {(*m).State = RUNNING;}
	
}	
/*
匀速中返回1
匀速进程结束返回2

*/
static void motor_keep(motor *m)
{ 
	static int i = 0;
	i++;
	if(i == 16*((*m).step)) {i = 0; (*m).State = SLOWING;}
	else (*m).State = RUNNING;

}
/*
减速中 返回2
减速完毕 返回3
*/
static void motor_slower(motor *m)
{
	if((*m).cur_delay < (*m).max_delay)
	{
		(*m).cur_delay+=((*m).max_delay-(*m).min_delay)/24;
		TIM_SetAutoreload(TIM3,(*m).cur_delay);
		TIM_SetCompare2(TIM3,((*m).cur_delay)/2);
		(*m).State = SLOWING;
	}
	else (*m).State = STOPING;
}

static void Dir_Toggle(motor *m)
{
	MOTOR_CMD(MOTOR1_TIM, DISABLE);
	(*m).dir ^=1;
	(*m).min_delay = (*m).next_delay;
	delay_ms(200);
	if((*m).dir == CW)
	{MOTOR1_DIR_CW;}
	else
	{MOTOR1_DIR_CCW;}
	(*m).State = FASTING;
	//(*m).cur_delay = 12000;
	delay_ms(200);
	MOTOR_CMD(MOTOR1_TIM, ENABLE);

}
void motor_start(motor *m)
{
//	if(((*m).State == STOPING))
//	{

		MOTOR1_ENA_ON;
		MOTOR_CMD(MOTOR1_TIM,ENABLE);
//	}

}
void motor_stop(motor *m)
{
	if((*m).State == STOPING)
	{	
		MOTOR1_ENA_OFF;
		MOTOR_CMD(MOTOR1_TIM,DISABLE);
		(*m).dir ^=1; 
		MOTOR1_DIR_Toggle;
		(*m).State = FASTING;
	}
}

void speed_decision(motor *m)
{
			switch((*m).State){
					case FASTING:
						motor_faster(m);
						break;
					case RUNNING:
						motor_keep(m);
						break;
					case SLOWING:
						motor_slower(m);
						break;
					case STOPING:
						Dir_Toggle(m);  //方向反转
						break;		
				}

}

