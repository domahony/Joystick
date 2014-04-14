/*
 * Motor.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: domahony
 */

#include "Motor.h"
#include <cmath>
#include <iostream>

static int map(int raw, int rmin, int rmax, int omin, int omax);

Motor::Motor(Adafruit_DCMotor* m, Range in, Range out) : input(in), output(out), _motor(m)
{
	setSpeed(0);
}

void Motor::
setSpeed(const int& sp)
{
	int dir = RELEASE;
	int speed;
	if (sp == 0) {
		dir = RELEASE;
		speed = 0;
	} else if (sp < 0) {
		speed = map(std::abs(sp), input.min, input.max, output.min, output.max);
		dir = BACKWARD;
	} else {
		speed = map(sp, input.min, input.max, output.min, output.max);
		dir = FORWARD;
	}

	_motor->run(dir);
	_motor->setSpeed(speed);
}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

static int map(int raw, int rmin, int rmax, int omin, int omax)
{
	double rpct = static_cast<double>(raw - rmin)/(rmax - rmin);
	double optc = rpct * (omax - omin);
	return static_cast<int>(optc) + omin;
}
