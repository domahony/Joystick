/*
 * Motor.h
 *
 *  Created on: Apr 1, 2014
 *      Author: domahony
 */

#ifndef MOTOR_H_
#define MOTOR_H_

struct Range {
	Range(const int& min, const int& max) : min(min), max(max) {}
	int min;
	int max;
};

class Motor {
public:
	Motor(const int p1, const int p2, const int sp, Range in, Range out);
	virtual ~Motor();

	void setSpeed(const int& sp);

private:
	int inPin1;
	int inPin2;
	int speedPin;
	Range input;
	Range output;
};

#endif /* MOTOR_H_ */
