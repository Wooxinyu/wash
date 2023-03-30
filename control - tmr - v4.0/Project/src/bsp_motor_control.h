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
	/*��ǰ���״̬*/
	u8  State ; 
	/*��ת����*/
	u8  dir ;    
	/*��ǰ������*/
	int  cur_delay;  
	/*����Ȧ��*/
	int  step;
	/*���ת��*/
	u16  min_delay;
	/*����ת��*/
	u16  max_delay;
	
	u16 next_delay;

}motor;

motor motor_init(u16 ,u16);
void speed_decision(motor *);
void motor_start(motor *);
void motor_stop(motor *);
#endif



