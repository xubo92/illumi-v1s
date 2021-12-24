#include "stm32f4xx_hal.h"
#include <stdio.h>

/* -- for HAL_Init() -- */
void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_MspDeInit(void)
{
  __HAL_RCC_SYSCFG_CLK_DISABLE();
  __HAL_RCC_PWR_CLK_DISABLE();
}


/* -- for HAL_I2C_Init() -- */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hi2c->Instance==I2C3)
  {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
		/* I2C3 GPIO Configuration:  PC9 -> I2C3_SDA; PA8 -> I2C3_SCL */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C3_CLK_ENABLE();
  }

}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C3)
  {
    /* Peripheral clock disable */
    __HAL_RCC_I2C3_CLK_DISABLE();

    /* I2C3 GPIO Configuration: PC9 -> I2C3_SDA; PA8 -> I2C3_SCL */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8);
  }

}


/* -- for HAL_TIM_PWM_Init() -- */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	if(htim->Instance == TIM2)  // TIM2-CH1 and TIM2-CH3 are used by Motor 1 and 3
	{	
		// for Motor 1
		__HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock for GPIOA
		GPIO_InitStruct.Pin  = GPIO_PIN_15; // use GPIOA-PIN15 as AF mode
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM2; // refer to STM32F4 alternate function table
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		// for Motor 3
		__HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock for GPIOA
		GPIO_InitStruct.Pin  = GPIO_PIN_2; // use GPIOA-PIN2 as AF mode
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM2; // refer to STM32F4 alternate function table
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		__HAL_RCC_TIM2_CLK_ENABLE(); // Enable clock for TIM2
	}
	else if(htim->Instance == TIM1)  // PWM2 --> PB13 --> TIM1|CH1N for Motor 2
	{
		__HAL_RCC_GPIOB_CLK_ENABLE(); // Enable clock for GPIOB
		GPIO_InitStruct.Pin  = GPIO_PIN_13;  // use GPIOB-PIN13 as AF mode
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM1; // refer to STM32F4 alternate function table
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		__HAL_RCC_TIM1_CLK_ENABLE(); // Enable clock for TIM1
	}
	else if(htim->Instance == TIM3)
	{
		printf("TIM3 MspInit is not properly done ...");
	}
	
	
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim)
{
	if(htim->Instance == TIM2)
	{
		__HAL_RCC_TIM2_CLK_DISABLE();
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15);
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);
		
	}
	else if(htim->Instance == TIM1)
	{
		__HAL_RCC_TIM1_CLK_DISABLE();
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13);
	}
	else if(htim->Instance == TIM3)
	{
		printf("TIM3 MspDeInit is not properly done ...");
	}
}
