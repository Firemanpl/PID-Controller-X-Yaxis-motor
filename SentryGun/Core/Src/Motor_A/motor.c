/*
 * motor.c
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */
#include "main.h"
#define ENCODER_RESOLUTION			11
#define TIMER_CONF_BOTH_EDGE_T1T2	4

void motor_str_init(motor_str *m, TIM_HandleTypeDef *tim)
{
	m->timer = tim;
	m->pulse_count = 0;
	m->measured_speed = 0;
	m->set_target = 0;
	m->actual_PWM = 0;
}
void set_target(motor_str *m){
	motor_update_cout(m);
}

void motor_update_count(motor_str *m)
{

		static uint16_t LastTimerCounter = 0;
		int TimerDif = __HAL_TIM_GET_COUNTER(m->timer) - LastTimerCounter;
		if(TimerDif >= 4 || TimerDif <= -4)
		{
			TimerDif /= 4;
			m->pulse_count += (int8_t)TimerDif;
			LastTimerCounter = __HAL_TIM_GET_COUNTER(m->timer);
		}
}
