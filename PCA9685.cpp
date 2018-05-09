#include <PCA9685.h>
#include <Wire.h>

PCA9685::PCA9685(uint8_t address) 
{
	_address = BASE_ADDRESS | address;
}

void PCA9685::begin() 
{
	Wire.begin();
}

void PCA9685::init()
{
	reset();
}

void PCA9685::reset() 
{
	write8(MODE1, 0x00);
}

void PCA9685::setFREQ(float freq) 
{
	float prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	uint8_t prescale = floor(prescaleval + 0.5);

	uint8_t oldmode = read8(MODE1);
	uint8_t newmode = (oldmode & 0x7F) | 0x10; // sleep
	write8(MODE1, newmode); // go to sleep
	write8(PRESCALE, prescale); // set the prescaler
	write8(MODE1, oldmode);
	delay(5);
	write8(MODE1, oldmode | 0xA1);
}

void PCA9685::setDC(uint8_t num, uint16_t on, uint16_t off) 
{
	Wire.beginTransmission(_address);
	Wire.write(LED0_ON_L + (num << 2));
	Wire.write(on);
	Wire.write(on >> 8);
	Wire.write(off);
	Wire.write(off >> 8);
	Wire.endTransmission();
}

//either all on or off, using pin OE
void PCA9685::all(boolean state)
{
	for(byte i = 0; i < 16; i++)
	{
		if(state) //write all high
			setDC(i, 0, 4095);
		else //write all low
			setDC(i, 0, 0); 
	}
}

uint8_t PCA9685::read8(uint8_t addr) 
{
	Wire.beginTransmission(_address);
	Wire.write(addr);
	Wire.endTransmission();
	Wire.requestFrom((uint8_t)_address, (uint8_t)1);
	return Wire.read();
}

void PCA9685::write8(uint8_t addr, uint8_t d) 
{
	Wire.beginTransmission(_address);
	Wire.write(addr);
	Wire.write(d);
	Wire.endTransmission();
}
