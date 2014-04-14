/*
 * Wire.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: domahony
 */

#include "Wire.h"
#include <wiringPiI2C.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <cstdio>

namespace wire {

using std::cout;
using std::endl;
using std::hex;

uint8_t Wire::
read8(const uint8_t& reg) const
{
	int _fd = wiringPiI2CSetup(_i2c);

	::write(_fd, &reg, sizeof(reg));

	uint8_t ret = 0xFF;
	int err = ::read(_fd, &ret, sizeof(ret));

	if (err == -1) {
		perror(0);
	switch (errno) {
	case EBADF:
		std::cerr << "ERROR READING EBADF: " << errno << endl;
		break;
	case EFAULT:
		std::cerr << "ERROR READING EFAULT: " << errno << endl;
		break;
	case EINVAL:
		std::cerr << "ERROR READING EINVAL: " << errno << endl;
		break;
	case ENOTTY:
		std::cerr << "ERROR READING ENOTTY: " << errno << endl;
		break;
	default:
		std::cerr << "ERROR READING ???: " << errno << endl;
		break;
	}
	}

	cout << "Reading: "  << _fd << " 0x" << hex << static_cast<unsigned int>(reg) << " Value: 0x"
			<< hex << static_cast<unsigned int>(ret) << endl;
	close(_fd);

	return ret;
}

void Transmission::
end()
{
	int _fd = wiringPiI2CSetup(_i2c);
	::write(_fd, &_buf[0], _buf.size());

	cout << "Writing to " << _fd << " Reg: 0x" << hex << static_cast<unsigned int>(_buf[0])
			<< " 0x" << static_cast<unsigned int>(_buf[0]) << endl;

	close(_fd);
}

/*
void Wire::
send8(const uint8_t& addr, const uint8_t& reg, const uint8_t& data)
{
	int _fd = wiringPiI2CSetup(addr);
	int err;
	if ((err = wiringPiI2CWriteReg8(_fd, reg, data))) {
		std::cerr << "Failed writing: " << err << endl;
	}
	cout << "Writing to " << _fd << " Reg: 0x" << hex << static_cast<unsigned int>(reg)
			<< " 0x" << static_cast<unsigned int>(data) << endl;
	close(_fd);
}
*/

} /* namespace wire */
