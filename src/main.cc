/*
 * main.cc
 *
 *  Created on: Mar 30, 2014
 *      Author: domahony
 */

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <unistd.h>
#include <iostream>

int
main(int argc, char**argv)
{
	int naxis = 0;
	int nbuttons = 0;
	int fd = open("/dev/input/js0", O_RDONLY|O_NONBLOCK);

	ioctl(fd, JSIOCGAXES, &naxis);
	ioctl(fd, JSIOCGBUTTONS, &nbuttons);

	std::cout << "Number of Axis: " << naxis << std::endl;
	std::cout << "Number of Buttons: " << nbuttons << std::endl;

	while (1) {

		struct js_event e;
		while (read(fd, &e, sizeof(e)) > 0) {
			switch (e.type) {
			case JS_EVENT_AXIS:
				if (e.number != 7 && e.number != 6) {
					std::cout << "Axis: " << static_cast<int>(e.number);
					std::cout << " Value: " << static_cast<int>(e.value) << std::endl;
				}
				break;
			case JS_EVENT_BUTTON:
				std::cout << "Button: " << static_cast<int>(e.number);
				std::cout << " Value: " << static_cast<int>(e.value) << std::endl;
				break;
			default:
				break;
			}
		}

	}
}


