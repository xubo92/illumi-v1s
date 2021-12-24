/*
 * utils.c
 *
 *  Created on: Dec 19, 2021
 *  Author: Xubo Lyu
 */
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "utils.h"

// user error handle
void Error_Handler(void)
{
  __disable_irq();
	printf("Error detected, please debug the program");
  while (1)
  {}
}


