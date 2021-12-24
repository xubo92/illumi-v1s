/*
 * motor.h
 *
 *  Created on: Dec 18, 2021
 *  Author: Xubo Lyu
 */

//  (1)\    /(2)
//      \  /
//       \/  
//       /\	  illumi-v1s
//      /  \
//  (4)/    \(3)

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "stm32f4xx_hal.h"

// PWM1 --> PA15 --> TIM2-CH1
void Motor1_Init(uint16_t arr, uint16_t psc);
void Motor1_Set(uint16_t compare);


// PWM2 --> PB13 --> TIM1|CH1N
void Motor2_Init(uint16_t arr, uint16_t psc);
void Motor2_Set(uint16_t compare);

//// PWM3 --> PA2  --> TIM2|CH3
//void Motor3_Init(uint16_t arr, uint16_t psc);
//void Motor3_Set(uint16_t compare);
//
//// PWM4 --> PB4  --> TIM3|CH1
//void Motor4_Init(uint16_t arr, uint16_t psc);
//void Motor4_Set(uint16_t compare);

#endif
