/*
IO Driver for MCP3008 
8 channel AD converter

CLK = clock
Din = MOSI
Dout = MISO
ChipSelect = Slave select

Requires communicating via on-board pins
This ADC is nearly twice as fast as the regular on-board analog pins.

TODO:
	add support for multiple chips.

*/
#ifndef iodMCP3008_h
#define iodMCP3008_h

#include <IODriver.h>

class MCP3008 : public IODriver {
public:
	MCP3008(int clock, int dataIn, int dataOut, int chipSelect);

	void begin();

	int analogRead(int address);

private:
	int _resampleCount;
	int _delayTime;

	unsigned char _dataInMask;
	unsigned char _dataOutMask;
	unsigned char _clockMask;
	unsigned char _chipSelectMask;

	struct {
		bool clock;
		bool dataIn;
		bool dataOut;
		bool chipSelect;
	} _port;
};

#endif