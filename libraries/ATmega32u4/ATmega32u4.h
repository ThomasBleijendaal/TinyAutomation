/*
IO Driver for default ports of ATmega32u4 (i.e. Sparkfun Arduino Pro Micro)

Analog and digital addresses are on the same pins.

*/
#ifndef iodATmega32u4_h
#define iodATmega32u4_h

#include <IODriver.h>

//#define FASTDIGITAL

class ATmega32u4 : public IODriver {
public:
	ATmega32u4();

	void begin();
	void cycle();
	void mode(int address, int mode);

	bool digitalRead(int address);
	void digitalWrite(int address, bool data);

	int analogRead(int address);
	void analogWrite(int address, int data);
};


#endif