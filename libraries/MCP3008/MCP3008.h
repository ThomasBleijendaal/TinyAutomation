/*
IO Driver for MCP3008 (8 channel AD converter)

// Requires communicating via on-board pins

// TODO:
// replace digitalRead and Write with direct port manipulation. 

*/
#ifndef iodMCP3008_h
#define iodMCP3008_h

#include <IODriver.h>

class MCP3008 : public IODriver {
public:
	MCP3008(int resampleCount, int delayTime, int CLK, int Din, int Dout, int ChipSelect);

	void begin();
	int readData(int address);

private:
	int _resampleCount;
	int _delayTime;

	int _CLK;
	int _Din;
	int _Dout;
	int _CS;
};

#endif