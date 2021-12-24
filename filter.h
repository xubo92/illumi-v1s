/*
 * filter.h
 *
 *  Created on: Dec 16, 2021
 *  Author: Xubo Lyu
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

float Complementary_Filter(float AccAngle, float GyroAngleSpeed, float dt, float prevAngle);
void Calculate_Flt_Angle(float *fltedAttitude, short *accData, short *gyroData);

#endif /* INC_FILTER_H_ */
