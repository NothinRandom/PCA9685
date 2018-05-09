#ifndef _PCA9685_H
#define _PCA9685_H

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


#define SUBADR1 0x02
#define SUBADR2 0x03
#define SUBADR3 0x04

#define MODE1 0x00
#define PRESCALE 0xFE

#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

#define BASE_ADDRESS 0x40

class PCA9685
{
	public:
		PCA9685(uint8_t addr);
		void begin(void);
		void init(void);
		void reset(void);
		void setFREQ(float freq);
		void setDC(uint8_t num, uint16_t on, uint16_t off);
		void all(boolean state);
	private:
		uint8_t _address;
		uint8_t read8(uint8_t addr);
		void write8(uint8_t addr, uint8_t d);
};

#endif
