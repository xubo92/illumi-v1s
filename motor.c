/*
 * motor.c
 *
 *  Created on: Dec 18, 2021
 *  Author: Xubo Lyu
 */
 
#include "motor.h"

/* -----  Motor 1  ------*/
// PWM1 --> PA15 --> TIM2-CH1
void Motor1_Init(uint16_t arr, uint16_t psc)
{
	// TIM2 init
	TIM_HandleTypeDef TIM_InitStruct = {0};
	TIM_InitStruct.Instance = TIM2;
	TIM_InitStruct.Init.Prescaler = psc;
	TIM_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_InitStruct.Init.Period = arr;
	TIM_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_PWM_Init(&TIM_InitStruct); // this will call HAL_TIM_PWM_MspInit() at stm32f4_hal_msp.c where the related GPIOs are defined

	//TIM2 CH1 init
	TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
	TIM_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
	TIM_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_LOW;
	TIM_OC_InitStruct.Pulse = arr/2;
	HAL_TIM_PWM_ConfigChannel(&TIM_InitStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM_InitStruct, TIM_CHANNEL_1);
}

// PWM1 --> PA15 --> TIM2-CH1
void Motor1_Set(uint16_t compare)
{

	TIM2->CCR1=compare;

}


/* -----  Motor 2  ------*/
// PWM2 --> PB13 --> TIM1|CH1N
void Motor2_Init(uint16_t arr, uint16_t psc)
{
	// TIM1 init
	TIM_HandleTypeDef TIM_InitStruct = {0};
	TIM_InitStruct.Instance = TIM1;
	TIM_InitStruct.Init.Prescaler = psc;
	TIM_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_InitStruct.Init.Period = arr;
	TIM_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_PWM_Init(&TIM_InitStruct); // this function will call HAL_TIM_PWM_MspInit() at stm32f4_hal_msp.c where the related GPIOs are defined

	//TIM1 CH1N init
	TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
	TIM_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
	TIM_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_LOW;  //CH1
	TIM_OC_InitStruct.OCNPolarity = TIM_OCPOLARITY_HIGH; //CH1N
	TIM_OC_InitStruct.Pulse = arr/2;
	HAL_TIM_PWM_ConfigChannel(&TIM_InitStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM_InitStruct, TIM_CHANNEL_1);  //CH1
	HAL_TIMEx_PWMN_Start(&TIM_InitStruct, TIM_CHANNEL_1); //CH1N
	

}

// PWM2 --> PB13 --> TIM1|CH1N
void Motor2_Set(uint16_t compare)
{
	TIM1->CCR1=compare;
}



/* -----  Motor 3  ------*/
// PWM3 --> PA2  --> TIM2|CH3
//void Motor3_Init(uint16_t arr, uint16_t psc)
//{}


//void Motor3_Set(uint16_t compare)
//{}




/* -----  Motor 4  ------*/
//// PWM4 --> PB4  --> TIM3|CH1
//void Motor4_Init(uint16_t arr, uint16_t psc)
//{}


//void Motor4_Set(uint16_t compare)
//{}


