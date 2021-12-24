/*
 * imu.h
 *
 *  Created on: Dec 16, 2021
 *  Author: Xubo Lyu
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32f4xx_hal.h"


#define MPU6050_ADDR        (0x69<<1) // the AD0 of device is connected to VCC, so not 0x68 but 0x69
#define MPU6050_PWR_MGMT_1   0x6B  // power management
#define MPU6050_SMPLRT_DIV   0x19  // sample rate of gyro
#define MPU6050_CONFIG       0x1A
#define MPU6050_GYRO_CONFIG  0x1B
#define MPU6050_ACCEL_CONFIG 0x1C
#define MPU6050_WHO_AM_I     0x75
#define MPU6050_GYRO_OUT     0x43     //MPU6050 gyro out register addr
#define MPU6050_ACC_OUT      0x3B     //MPU6050 acc out register addr


// I2C3 used by IMU
void I2C3_Init(void);

// IMU functions
int MPU6050_Read_Register(uint8_t reg_addr, unsigned short len, uint8_t *data_ptr);
int MPU6050_Write_Register(uint8_t reg_addr, unsigned short len, uint8_t data);
void IMU_Init(void);
void IMU_Read_Acc(short *accData);
void IMU_Read_Gyro(short *gyroData);
uint8_t IMU_ID(void);

#endif /* INC_MPU6050_H_ */
