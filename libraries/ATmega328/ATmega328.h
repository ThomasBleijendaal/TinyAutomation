/*
IO Driver for default ports of ATmega328

Analog pins are moved to 20 - 27, since each pin requires to be unique.

// Requires communicating via on-board pins

// TODO:
// replace digitalRead and Write with direct port manipulation. 

*/
#ifndef iodATmega328_h
#define iodATmega328_h

#include <IODriver.h>

class ATmega328 : public IODriver {
public:
	ATmega328();

	void begin();
	void cycle();
	void mode(int address, int mode);

	bool digitalRead(int address);
	void digitalWrite(int address, bool data);

	int analogRead(int address);
	void analogWrite(int address, int data);
};


#endif