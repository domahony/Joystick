/*
 * Motor.h
 *
 *  Created on: Apr 1, 2014
 *      Author: domahony
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Adafruit_MotorShield.h"

struct Range {
	Range(const int& min, const int& max) : min(min), max(max) {}
	int min;
	int max;
};

class Motor {
public:
	Motor(Adafruit_DCMotor* m, Range in, Range out);
	virtual ~Motor();

	void setSpeed(const int& sp);

private:
	Range input;
	Range output;
	Adafruit_DCMotor *_motor;
};

#endif /* MOTOR_H_ */
