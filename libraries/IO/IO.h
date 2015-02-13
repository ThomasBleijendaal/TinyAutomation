/*
IO abstraction layer.

Register IO drivers in order to extend the IO range.

TODO:
	- Improve handling of IO errors
	- Driver count should be dynamic
	- Check pin usage

*/
#ifndef IO_h
#define IO_h

#include <IODriver.h>

// IO Driver types
#define IOinstant 1
#define IOinstantCycle 2
#define IOinterrupt 10

class IO {
public:
	IO();
	IO(int driverCount);

	void registerDriver(int rangeLow, int rangeHigh, IODriver * driver, int driverType);

	void begin();
	void cycle();
	void interrupt();

	void mode(int address, int mode);

	bool digitalRead(int address);
	void digitalWrite(int address, bool data);
	
	int analogRead(int address);
	float formattedRead(int address);
	void analogWrite(int address, int data);

private:
	int _driverCount;
	int _cycleDriverCount;
	int _interruptDriverCount;

	IODriver ** _drivers;
	int * _addressLow;
	int * _addressHigh;

	int * _cycleDrivers;
	int * _interruptDrivers;
};

#endif