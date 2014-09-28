/*
IO abstraction layer.

Register IO drivers in order to extend the IO range.

TODO:
	- Differentiate between types of IO Drivers
	- Improve handling of IO errors
	- Support all forms of IO (analog and digital)
	- Improve looping through drivers
	- Driver count should be dynamic

*/
#ifndef IO_h
#define IO_h

#include <IODriver.h>

class IO {
public:
	IO();
	IO(int driverCount);

	void registerDriver(int rangeLow, int rangeHigh, IODriver * driver);

	void begin();
	void cycle();
	void mode(int address, int mode);

	bool digitalRead(int address);
	void digitalWrite(int address, bool data);
	
	int analogRead(int address);
	void analogWrite(int address, int data);

private:
	int _driverCount;
	int _filledSlot;

	IODriver ** _drivers;
	int * _pinLayout;
};

#endif