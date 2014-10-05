/*
IO Driver for MCP23016 
16 channel DIO converter

TODO:
	support Interrupt output
	support IO speed settings
	support multiple addresses
	support INPUT_PULLUP
	remove whiles
	improve reading of data, de datasheet indicates that it can be faster.

Speedtest:
	First implementation:	65929 ms

*/
#ifndef iodMCP23016_h
#define iodMCP23016_h

#include <IODriver.h>

#define GP0 0x00
#define GP1 0x01
#define LAT0 0x02
#define LAT1 0x03
#define POL0 0x04
#define POL1 0x05
#define DIR0 0x06
#define DIR1 0x07
#define INT0 0x08
#define INT1 0x09
#define IOCON 0x0A

union MCP23016_dataWord {
	unsigned int data;

	struct b_t {
		unsigned char lo;
		unsigned char hi;
	} bytes;

	MCP23016_dataWord() {
		data = 0;
	}
};

class MCP23016 : public IODriver {
public:
	MCP23016(int address);

	void begin();
	void cycle();
	void mode(int address, int mode);

	bool digitalRead(int address);
	void digitalWrite(int address, bool data);

private:
	unsigned char _address;
	
	MCP23016_dataWord _read;
	MCP23016_dataWord _write;
	MCP23016_dataWord _modes;
	MCP23016_dataWord _inputPolarity;

	union {
		unsigned char all;
		struct {
			// dimensions must be included, otherwise each bool will occupy a char and the union will be 6 chars wide. //
			bool modesLo : 1;
			bool modesHi : 1;
			bool inputPolarityLo : 1;
			bool inputPolarityHi : 1;
			bool writesLo : 1;
			bool writesHi : 1;
		};
	} _send;
	
};

#endif