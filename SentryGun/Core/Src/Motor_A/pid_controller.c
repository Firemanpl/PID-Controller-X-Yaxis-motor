/*
 * pid_controller.c
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */

#include "main.h"
#include <math.h>
void PID_Init(motor_str *m, float kp_init, float ki_init, float kd_init,
		int min, int max) {
	m->kp = kp_init;
	m->ki = ki_init;
	m->kd = kd_init;
	m->min = min;
	m->max = max;
	m->motorDirection = Direct;
}

void PID_calculate(motor_str *m) {
	float previousTime;
	float previousError;  //for calculating the derivative (edot)
	float errorIntegral; //integral error
	float deltaTime;  //time difference
	float errorValue;  //error
	float edot; //derivative (de/dt)
	float currentTime = HAL_GetTick();
	deltaTime = (currentTime - previousTime) / 10e6;
	previousTime = currentTime;
	errorValue = (float) m->pulse_count - (float) m->set_target;
	edot = (errorValue - previousError) / deltaTime;
	errorIntegral = errorIntegral + errorValue + deltaTime;
	float controlSignal = (m->kp * errorValue) + (m->kd * edot)
			+ (m->ki * errorIntegral);

	if ((int)controlSignal < 0) //negative value: CCW
		m->motorDirection = -1;
	else if ((int)controlSignal > 0) //positive: CW
		m->motorDirection = 1;
	m->actual_PWM = (int) fabs(controlSignal);
	if (m->actual_PWM > m->max)
		m->actual_PWM = m->max;
	else if (m->actual_PWM < m->min && errorValue != 0)
		m->actual_PWM = m->min;

	previousError = errorValue;
}
