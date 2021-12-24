/*
 * imu.c
 *
 *  Created on: Dec 16, 2021
 *  Author: Xubo Lyu
 */
#include <stdio.h>
#include "imu.h"
#include "utils.h"

extern I2C_HandleTypeDef hi2c3;

void I2C3_Init(void)
{
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)  //  this will call HAL_I2C_MspInit() at stm32f4_hal_msp.c where the related GPIOs are defined
  {
    printf("Fail to initialize I2C3");
  }
}


int MPU6050_Read_Register(uint8_t reg_addr, unsigned short len, uint8_t *data_ptr)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Read(&hi2c3, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data_ptr, len, 1000);
	if (status != HAL_OK)
	{
		Error_Handler();
	}
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {}
	while (HAL_I2C_IsDeviceReady(&hi2c3, MPU6050_ADDR, 1000, 1000) == HAL_TIMEOUT);
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {}
	return status;
}

int MPU6050_Write_Register(uint8_t reg_addr, unsigned short len, uint8_t data)
{
	HAL_StatusTypeDef status = HAL_OK;
  status = HAL_I2C_Mem_Write(&hi2c3, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, len, 1000);
  if (status != HAL_OK)
	{
      Error_Handler();
  }
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {}
	while (HAL_I2C_IsDeviceReady(&hi2c3, MPU6050_ADDR, 1000, 1000) == HAL_TIMEOUT);
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {}
	return status;
}



uint8_t IMU_ID(void) 
{
	uint8_t res = 0;
  MPU6050_Read_Register(MPU6050_WHO_AM_I, 1, &res);
	if (res != 0x68)
	{
		printf("MPU6050 not found ...");
		return 0;
	}
	else
	{
		printf("MPU6050 ID = %d\r\n",res);
		return 1;
	}
}


void IMU_Init(void)
{
	I2C3_Init();
	
	int i=0,j=0;
	for (i=0; i<1000; i++) // delay in case of error
	{
		 for (j=0; j<1000; j++) {}
	}

	// Wake up the sensor
	MPU6050_Write_Register(MPU6050_PWR_MGMT_1, 1, 0x00);
  // gyro config
	MPU6050_Write_Register(MPU6050_SMPLRT_DIV, 1, 0x07);  // gyro sample rate
	MPU6050_Write_Register(MPU6050_CONFIG, 1, 0x06);
	MPU6050_Write_Register(MPU6050_GYRO_CONFIG, 1, 0x18); // not do self-check, and 2000 deg/s
	// accel config
	MPU6050_Write_Register(MPU6050_ACCEL_CONFIG, 1, 0x01); // 16g mode

}

// read acc data and save them into array accData
void IMU_Read_Acc(short *accData)
{
   uint8_t buf[6];
   MPU6050_Read_Register(MPU6050_ACC_OUT, 6, buf);
   accData[0] = (buf[0] << 8) | buf[1];
   accData[1] = (buf[2] << 8) | buf[3];
   accData[2] = (buf[4] << 8) | buf[5];
}

// read gyro data and save them into array gyroData
void IMU_Read_Gyro(short *gyroData)
{
   uint8_t buf[6];
   MPU6050_Read_Register(MPU6050_GYRO_OUT, 6, buf);
   gyroData[0] = (buf[0] << 8) | buf[1];
   gyroData[1] = (buf[2] << 8) | buf[3];
   gyroData[2] = (buf[4] << 8) | buf[5];
}

