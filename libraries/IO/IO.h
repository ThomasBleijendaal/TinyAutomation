/*
IO abstraction layer.

Register IO drivers in order to extend the IO range.

TODO:
	- Differentiate between types of IO Drivers
	- Improve handling of IO errors
	- Support all forms of IO (analog and digital)
	- 

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

	void digitalWrite(int address, bool data);
	
	int analogRead(int address);
	void analogWrite(int address, int data);

private:
	int _driverCount;
	int _filledSlot;

	IODriver ** _drivers;
	int * _pinLayout;
};

class DefaultDriver : public IODriver {	
public:
	DefaultDriver();

	void begin();
	int readData(int address);
	void writeData(int address, bool data);
	void writeData(int address, int data);
	void cycle();
};

#endif