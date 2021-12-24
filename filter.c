/*
 * filter.c
 *
 *  Created on: Dec 16, 2021
 *  Author: Xubo Lyu
 */

#include "filter.h"
#include "math.h"


// First-order Complementary Filter
// prevAngle: last time return of complementart filter
float Complementary_Filter(float accAngle, float gyroAngleSpeed, float dt, float prevAngle)
{
    float a = 0.98f;
    float angle = 0;
    angle = a * (prevAngle + gyroAngleSpeed * dt) + (1 - a) * (accAngle);
    return angle;
}




// fltedAttitude: filtered ; accData: raw acc input; gyroData: raw gyro input
void Calculate_Flt_Angle(float *fltedAttitude, short *accData, short *gyroData)
{
	float c_accData[3], c_gyroData[3];
	float xz_accAngle, yz_accAngle, xz_gyroAngleSpeed, yz_gyroAngleSpeed;
	c_accData[0] = accData[0] / 2048.0f;  // 16g range
	c_accData[1] = accData[1] / 2048.0f;
	c_accData[2] = accData[2] / 2048.0f;

	c_gyroData[0] = gyroData[0] / 16.4f;  // 2000deg/s
	c_gyroData[1] = gyroData[1] / 16.4f;
	c_gyroData[2] = gyroData[2] / 16.4f;

	xz_accAngle = atan2f(c_accData[0], c_accData[2]) / 3.14f * 180.0f;
	yz_accAngle = atan2f(c_accData[1], c_accData[2]) / 3.14f * 180.0f;

	xz_gyroAngleSpeed = c_gyroData[1];
	yz_gyroAngleSpeed = c_gyroData[0];

	// do complementary filtering
	float dt = 0.005f;
	fltedAttitude[0] = Complementary_Filter(xz_accAngle, xz_gyroAngleSpeed, dt, fltedAttitude[0]);
	fltedAttitude[1] = Complementary_Filter(yz_accAngle, yz_gyroAngleSpeed, dt, fltedAttitude[1]);
}
