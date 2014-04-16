/*
 * Chassis.h
 *
 *  Created on: Apr 1, 2014
 *      Author: domahony
 */

#ifndef CHASSIS_H_
#define CHASSIS_H_

#include "Motor.h"
#include <cmath>
#include <iostream>

enum Direction {
	_LEFT,
	_RIGHT,
	_FORWARD,
	_BACKWARD,
};


class Chassis {
public:
	Chassis() : afms(),
		left_front(afms.getMotor(1), Range(0, 128), Range(0, 255)),
		left_rear(afms.getMotor(2), Range(0, 128), Range(0, 255)),
		right_front(afms.getMotor(3), Range(0, 128), Range(0, 255)),
		right_rear(afms.getMotor(4), Range(0, 128), Range(0, 255)),
		speed(0), direction(_FORWARD) {

		afms.begin(60);

	}

	void set_speed(const int& sp) {
		speed = sp;
		engage();
	}

	void set_direction(enum Direction dir) {

		direction = dir;
		engage();
	}

	virtual ~Chassis() {

	}

private:


	void engage() {

		switch (direction) {
		case _FORWARD:
			forward();
			break;
		case _BACKWARD:
			reverse();
			break;
		case _LEFT:
			turn_left();
			break;
		case _RIGHT:
			turn_right();
			break;
		}
	}

	void turn_left() {
		std::cout << "CHASSIS: Left: " << speed << std::endl;
		left_front.setSpeed(-speed);
		left_rear.setSpeed(-speed);
		right_front.setSpeed(speed);
		right_rear.setSpeed(speed);
	}

	void turn_right() {
		std::cout << "CHASSIS: Right: " << speed << std::endl;
		left_front.setSpeed(speed);
		left_rear.setSpeed(speed);
		right_front.setSpeed(-speed);
		right_rear.setSpeed(-speed);
	}

	void forward() {
		std::cout << "CHASSIS: Forward: " << speed << std::endl;
		left_front.setSpeed(speed);
		left_rear.setSpeed(speed);
		right_front.setSpeed(speed);
		right_rear.setSpeed(speed);
	}

	void reverse() {
		std::cout << "CHASSIS: Reverse: " << speed << std::endl;
		left_front.setSpeed(-speed);
		left_rear.setSpeed(-speed);
		right_front.setSpeed(-speed);
		right_rear.setSpeed(-speed);
	}

	int speed;
	enum Direction direction;
	Adafruit_MotorShield afms;
	Motor left_front;
	Motor left_rear;
	Motor right_front;
	Motor right_rear;

};

#endif /* CHASSIS_H_ */
