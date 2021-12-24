#include <stdio.h>
#include "stm32f4xx_hal.h"

// user header files
#include "imu.h"
#include "filter.h"
#include "motor.h"
#include "pid.h"



// global variables declaration
extern volatile unsigned int Task_Delay[3];
extern I2C_HandleTypeDef hi2c3;



// global variables definition
I2C_HandleTypeDef hi2c3 = {0};
volatile unsigned int Task_Delay[3] = {500, 5, 10};


int main(void)
{
	
	HAL_Init();
	
	
	IMU_Init();
	Motor1_Init(400-1, 16-1);
	Motor2_Init(400-1, 16-1);

	short Acel[3], Gyro[3];
	float fltedAtti[3];
	
	uint8_t  dir=1;
  uint16_t pwmval=0;
	
  if(IMU_ID() == 1)
  {
  	printf("MPU6050 Detected!");
	}
	else
  {
		printf("Cannot find MPU6050!");
		return 0;
  }
	
	while(1)
	{
		if(Task_Delay[0] == 0)
		{
			// task 0: printf
			printf("filtered xz angle = %f\n", (double)fltedAtti[0]);
			printf("filtered yz angle = %f\n", (double)fltedAtti[1]);
			Task_Delay[0] = 500;  // 2hz
		}
		
		if(Task_Delay[1] == 0)
		{
			// task 1: imu filter
			IMU_Read_Acc(Acel);
			IMU_Read_Gyro(Gyro);
			Calculate_Flt_Angle(fltedAtti, Acel, Gyro);
			Task_Delay[1] = 5;   // 200hz
			
		}
		
		if(Task_Delay[2] == 0)
		{
			// task 2: motor control
			(dir) ? pwmval++ : pwmval--;
			
			if(pwmval>300)
			{ 
				dir=0; 
			}
			
			if(pwmval==0)
			{ 
				dir=1; 
			}
			
			Motor1_Set(pwmval);
			Motor2_Set(pwmval);
			Task_Delay[2] = 10;
		}
	}
  
 
}



