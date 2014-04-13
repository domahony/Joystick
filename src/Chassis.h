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
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD,
};


class Chassis {
public:
	Chassis() : left(5,4,1, Range(0, 128), Range(450, 1024)), right(2, 7, 1, Range(0, 128), Range(450, 1024)), speed(0), direction(FORWARD) {

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
		case FORWARD:
			forward();
			break;
		case BACKWARD:
			reverse();
			break;
		case LEFT:
			turn_left();
			break;
		case RIGHT:
			turn_right();
			break;
		}
	}

	void turn_left() {
		std::cout << "CHASSIS: Left: " << speed << std::endl;
		left.setSpeed(-speed);
		right.setSpeed(speed);
	}

	void turn_right() {
		std::cout << "CHASSIS: Right: " << speed << std::endl;
		left.setSpeed(speed);
		right.setSpeed(-speed);
	}

	void forward() {
		std::cout << "CHASSIS: Forward: " << speed << std::endl;
		left.setSpeed(speed);
		right.setSpeed(speed);
	}

	void reverse() {
		std::cout << "CHASSIS: Reverse: " << speed << std::endl;
		left.setSpeed(-speed);
		right.setSpeed(-speed);
	}

	int speed;
	enum Direction direction;
	Motor left;
	Motor right;

};

#endif /* CHASSIS_H_ */
