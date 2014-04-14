/*************************************************** 
  This is a library for our Adafruit 16-channel PWM & Servo driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_PWMServoDriver.h>
#include "Wire.h"
#include "Serial.h"
#include <cmath>
#include <wiringPi.h>

using wire::Serial;
using std::floor;

Adafruit_PWMServoDriver::Adafruit_PWMServoDriver(uint8_t addr) : _wire(addr) {
}

void Adafruit_PWMServoDriver::begin(void) {
 reset();
}


void Adafruit_PWMServoDriver::reset(void) {
 write8(PCA9685_MODE1, 0x0);
}

void Adafruit_PWMServoDriver::setPWMFreq(float freq) {
  //Serial.print("Attempting to set freq ");
  //Serial.println(freq);
  
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;
  Serial::print("Estimated pre-scale: "); Serial::println(prescaleval);
  uint8_t prescale = floor(prescaleval + 0.5);
  Serial::print("Final pre-scale: "); Serial::println(prescale);
  
  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
  write8(PCA9685_MODE1, newmode); // go to sleep
  read8(PCA9685_MODE1);
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  read8(PCA9685_PRESCALE);
  write8(PCA9685_MODE1, oldmode);
  read8(PCA9685_MODE1);
  delay(5);
  write8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
                                          // This is why the beginTransmission below was not working.
  read8(PCA9685_MODE1);
  //  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
}

void Adafruit_PWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  //Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);

  /*
  write8((uint8_t)LED0_ON_L+4*num, (uint8_t)on);
  write8((uint8_t)(LED0_ON_L+4*num) + 1, (uint8_t)(on>>8));
  write8((uint8_t)(LED0_ON_L+4*num) + 2, (uint8_t)off);
  write8((uint8_t)(LED0_ON_L+4*num) + 3, (uint8_t)(off>>8));
  */

	wire::Transmission t = _wire.get_transmission();

	t.write((uint8_t)LED0_ON_L+4*num);
	t.write((uint8_t)on);
	t.write((uint8_t)(on>>8));
	t.write((uint8_t)off);
	t.write((uint8_t)(off>>8));
	t.end();

  /*
  _wire.beginTransmission(_i2caddr);
  _wire.send((uint8_t)LED0_ON_L+4*num);
  _wire.send((uint8_t)on);
  _wire.send((uint8_t)(on>>8));
  _wire.send((uint8_t)off);
  _wire.send((uint8_t)(off>>8));
  _wire.endTransmission();
  */
}

uint8_t Adafruit_PWMServoDriver::read8(uint8_t addr) {
	/*
  _wire.beginTransmission(_i2caddr);
  _wire.send(addr);
  _wire.endTransmission();

  _wire.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  return _wire.receive();
  */

  return _wire.read8(addr);
}

void Adafruit_PWMServoDriver::write8(uint8_t addr, uint8_t d) {

	wire::Transmission t = _wire.get_transmission();
	t.write(addr);
	t.write(d);
	t.end();
}
