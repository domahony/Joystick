/*
 * Motor.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: domahony
 */

#include "Motor.h"
#include <cmath>
#include <wiringPi.h>
#include <iostream>

static int map(int raw, int rmin, int rmax, int omin, int omax);

struct Direction {
	bool p1;
	bool p2;
};

static Direction FORWARD = {true, false};
static Direction REVERSE = {false, true};
static Direction STOP = {false, false};

Motor::Motor(const int p1, const int p2, const int sp, Range in, Range out) : inPin1(p1), inPin2(p2), speedPin(sp), input(in), output(out)
{
	wiringPiSetup();
	pinMode(inPin1, OUTPUT);
	pinMode(inPin2, OUTPUT);
	pinMode(speedPin, PWM_OUTPUT);
	setSpeed(0);
}

void Motor::
setSpeed(const int& sp)
{
	Direction dir = STOP;
	int speed;
	if (sp == 0) {
		dir = STOP;
		speed = 0;
	} else if (sp < 0) {
		speed = map(std::abs(sp), input.min, input.max, output.min, output.max);
		dir = REVERSE;
	} else {
		speed = map(sp, input.min, input.max, output.min, output.max);
		dir = FORWARD;
	}


	std::cout << "PINS: (" << inPin1 << ") (" << inPin2 << ") (" << speedPin << ")" << std::endl;
	std::cout << "PINS: (" << dir.p1 << ") (" << dir.p2 << ") (" << sp << ")" << std::endl;
	digitalWrite(inPin1, dir.p1);
	digitalWrite(inPin2, dir.p2);
	pwmWrite(speedPin, speed);
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
