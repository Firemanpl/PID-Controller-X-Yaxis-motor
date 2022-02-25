/*
 * L298N_5AD.h
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */

#ifndef SRC_L298N_5AD_H_
#define SRC_L298N_5AD_H_

typedef enum
{
	Direct = 0,
	Reverse = 1,
	Breake = 3
}L298N_5AD_Direction;

void L298N_5AD_init();
void L298N_5AD_set_motorA(uint16_t, L298N_5AD_Direction);
void L298N_5AD_set_motorA_Breake();


#endif /* SRC_L298N_5AD_H_ */
