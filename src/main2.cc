/*
 * main2.cc
 *
 *  Created on: Mar 30, 2014
 *      Author: domahony
 */


#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "Chassis.h"
#include <cstdio>

static void handle_abs(Chassis& c, const struct input_event& ie);
static void handle_key(Chassis& c, const struct input_event& ie);
static void init(const int& fd);
static void do_effect(const int& fd);

static struct input_absinfo absinfo[ABS_CNT];


int
main(int argc, char**argv)
{
	int fd = open("/dev/input/event0", O_RDONLY);

	Chassis c;

	struct input_event ie;

	init(fd);

	while (1) {
		while (read(fd, &ie, sizeof(ie)) > 0) {

			switch (ie.type) {
			case EV_ABS:
				handle_abs(c, ie);
				break;
			case EV_KEY:
				handle_key(c, ie);
				break;
			case EV_SYN:
				break;
			default:
				//std::cout << std::hex << "Type: " << ie.type << " Code: " << ie.code << " Value: " << ie.value << std::endl << std::endl;
				;
			}
		}
	}

}

static void handle_abs(Chassis& chassis, const struct input_event& ie)
{
	int value = ie.value;
	int min = absinfo[ie.code].minimum;
	int max = absinfo[ie.code].maximum;


	if (value < min) {
		value = min;
	}

	if (value > max) {
		value = max;
	}

	double pct = static_cast<double>(value)/max;

	switch (ie.code) {
	case 0x29:
		break;
	case ABS_Z:
		std::cout << "PCT: " << std::scientific << pct << std::endl;
		printf("PCT %12.6f\n", pct);
		std::cout << "Move Z: " << std::dec << ie.value << "(" << max << ")"<< std::endl;

		if (value > 128) {
			value = 0;
		} else {
			value -= 128;
		}
		chassis.set_speed(value);

		break;
	case ABS_X:
		std::cout << "PCT: " << std::scientific << pct << std::endl;
		printf("PCT %12.6f\n", pct);
		std::cout << "Move X: " << std::dec << ie.value << "(" << max << ")" << std::endl;
		break;
	case ABS_Y:
		std::cout << "PCT: " << std::scientific << pct << std::endl;
		printf("PCT %12.6f\n", pct);
		std::cout << "Move Y: " << std::dec << ie.value << "(" << max << ")" << std::endl;
		break;
	case ABS_RZ:
		std::cout << "PCT: " << std::scientific << pct << std::endl;
		printf("PCT %12.6f\n", pct);
		std::cout << "Rotate Z: " << std::dec << ie.value << "(" << max << ")" << std::endl;
		break;
	case ABS_HAT0X:

		if (ie.value == 0) {
			chassis.set_direction(FORWARD);
			chassis.set_speed(0);
		} else if (ie.value < 0) {
			chassis.set_direction(LEFT);
		} else {
			chassis.set_direction(RIGHT);
		}

		break;
	case ABS_HAT0Y:
		if (ie.value == 0) {
			chassis.set_direction(FORWARD);
			chassis.set_speed(0);
		} else if (ie.value > 0) {
			chassis.set_direction(BACKWARD);
		} else {
			chassis.set_direction(FORWARD);
		}

		break;
	default:
		std::cout << "PCT: " << std::scientific << pct << std::endl;
		printf("PCT %6.12f\n", pct);
		std::cout << std::hex << "ABS Type: " << ie.type << " Code: " << ie.code << " Value: " << ie.value << "(" << max << ")" << std::endl << std::endl;
		break;
	}
}

static void handle_key(Chassis& chassis, const struct input_event& ie)
{
	int button_num = ie.code & ~BTN_JOYSTICK;
	std::cout << "Button: "  << std::hex << button_num << " (" << ie.code << ")";
	if (ie.value) {
		std::cout << " Pressed"  << std::endl;
	} else {
		std::cout << " Released"  << std::endl << std::endl;
	}
}


static void
init(const int& fd)
{
	unsigned char bytes[(ABS_CNT/8) + 1];
	ioctl(fd, EVIOCGBIT(EV_ABS, (ABS_CNT/8) + 1), bytes);
	memset(absinfo, 0, sizeof(absinfo));

	std::cout << "Abs Features" << std::endl;
	for (int i = 0; i < sizeof bytes; i++) {
		//std::cout << std::hex << static_cast<int>(bytes[i]) << std::endl;

		for (int b = 0; b < 8; b++) {
			int bitnum = i * 8 + b;
			bool set = (bytes[i] >> b) & 0x1;
			std::cout << "Bitnum: " << std::hex << bitnum << ": " << static_cast<int>(bytes[i] >> b & 0x1) << std::endl;

			if (set) {
				ioctl(fd, EVIOCGABS(bitnum), &absinfo[bitnum]);

				std::cout << std::dec;
				std::cout << "     Value: "  << absinfo[bitnum].value << std::endl;
				std::cout << "     Minimum: "  << absinfo[bitnum].minimum << std::endl;
				std::cout << "     Maximum: "  << absinfo[bitnum].maximum << std::endl;
				std::cout << "     Fuzz: "  << absinfo[bitnum].fuzz << std::endl;
				std::cout << "     Flat: "  << absinfo[bitnum].flat << std::endl;
			}
		}
	}

	unsigned char bytes2[(FF_CNT/8) + 1];
	ioctl(fd, EVIOCGBIT(EV_FF, (FF_CNT/8) + 1), bytes2);

	std::cout << "FF Features" << std::endl;
	for (int i = 0; i < sizeof bytes2; i++) {
		for (int b = 0; b < 8; b++) {

			int bitnum = i * 8 + b;
			bool set = (bytes2[i] >> b) & 0x1;
			std::cout << "Bitnum: " << std::hex << bitnum << ": " << static_cast<int>(bytes2[i] >> b & 0x1) << std::endl;

		}

	}

}

static void
do_effect(const int& fd)
{
}
