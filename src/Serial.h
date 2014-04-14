/*
 * Serial.h
 *
 *  Created on: Apr 11, 2014
 *      Author: domahony
 */

#ifndef SERIAL_H_
#define SERIAL_H_

namespace wire {

class Serial {
public:
	Serial();

	static void print(const char* msg) {

	}

	static void println(const char *msg) {
		print(msg);
		print("\n");
	}

	static void print(const float& fl) {

	}

	static void println(const float& fl) {
		print(fl);
		print("\n");
	}

	virtual ~Serial();
};

} /* namespace wire */

#endif /* SERIAL_H_ */
