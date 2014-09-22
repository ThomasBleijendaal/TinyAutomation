/*
IO Driver for HC595 Shift Register (8 bit out)

// Requires communicating via on-board pins

// TODO:
// replace dependency on PORTD to dynamic port.

*/
#ifndef iodHC595_h
#define iodHC595_h

#include <IODriver.h>

class HC595 : public IODriver {
public:
	HC595(int dataPin, int clockPin, int latchPin, int chainLength);
	
	void begin();
	void cycle();

	void digitalWrite(int address, bool data);

private:
	int _dataPin;
	int _clockPin;
	int _latchPin;
	int _chainLength;

	unsigned char _dataPinMask;
	unsigned char _clockPinMask;
	unsigned char _latchPinMask;

	bool _writeRequired;
	bool* _writeData;
};

#endif