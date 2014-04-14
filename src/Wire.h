/*
 * Wire.h
 *
 *  Created on: Apr 11, 2014
 *      Author: domahony
 */

#ifndef WIRE_H_
#define WIRE_H_

#include "Types.h"
#include <stdint.h>
#include <vector>

namespace wire {


class Transmission {
public:
	void write(const uint8_t& data) {
		_buf.push_back(data);
	}
	virtual ~Transmission() {}

	void end();

private:
	Transmission(const uint8_t& addr) : _buf(), _i2c(addr) {};
	std::vector<uint8_t> _buf;
	const uint8_t& _i2c;

	friend class Wire;
};

class Wire {
public:
	Wire(const uint8_t& addr) : _i2c(addr) {};
	virtual ~Wire() {};

	uint8_t read8(const uint8_t& reg) const;
	Transmission get_transmission() {
		return Transmission(_i2c);
	}

private:
	const uint8_t _i2c;

};

} /* namespace wire */

#endif /* WIRE_H_ */
