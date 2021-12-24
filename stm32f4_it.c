#include "stm32f4xx_hal.h"
#include "stm32f4_it.h"


extern volatile unsigned int Task_Delay[3];

void SysTick_Handler(void)
{
	unsigned char i;
	for(i=0; i<3; i++)
	{
		if(Task_Delay[i])
		{
			Task_Delay[i]--;
		}
	}
  HAL_IncTick();

}
