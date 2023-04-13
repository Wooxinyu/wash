#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H
#include "stm32f10x.h"

#define FASTING 1
#define RUNNING 2
#define SLOWING 3
#define STOPING 4


#define CW   1
#define CCW  0


#define MAX_DELAY 14000
 
typedef struct 
{
	/*当前电机状态*/
	u8  State ; 
	/*旋转方向*/
	u8  dir ;    
	/*当前脉冲间隔*/
	int  cur_delay;  
	/*匀速圈数*/
	int  step;
	/*最快转速*/
	u16  min_delay;
	/*最慢转速*/
	u16  max_delay;
	
	u16 next_delay;

}motor;

motor motor_init(u16 ,u16);
void speed_decision(motor *);
void motor_start(motor *);
void motor_stop(motor *);
#endif



