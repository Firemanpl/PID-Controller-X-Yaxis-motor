/*
 * pid_controller.h
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */
#define MOTOR_A_Kp					1.2
#define MOTOR_A_Ki					0.1
#define MOTOR_A_Kd					0.2
#ifndef INC_PID_CONTROLLER_H_
#define INC_PID_CONTROLLER_H_
void PID_Init(motor_str *,float , float , float, int, int );
void PID_calculate(motor_str *);

#endif /* INC_PID_CONTROLLER_H_ */
