/*
IO Driver class

An abstract class which provides a basic structure for the IO class to interact with. 
The IO driver class gives the posibility to write highly specialized drivers for various IO extenders, like Shift Registers or Analog to Digital Converters.

Two types of IO drivers are foreseen:
- Instant
	This type of driver is very quick and can, if needed, be used every cycle.
	For example, a A2D Converter, as these sample speeds are well above 1ksps and are very fast communicators.
	These drivers do not require the cycle()-method, but manipulate the IO instantly. But, in some cases, a cycle()-method
	can be used.
- Interruptive
	This type of driver is slow, and requires various delays in order to communicate with the corresponding hardware. 
	Often, these drivers work with hardware which meassure a physical quantity which is invariant, for example a barometer.
	These drivers require the cycle()-method, which is periodically called by IO, and the read and write methods interact on a buffer.

*/
#ifndef IODriver_h
#define IODriver_h

// IO object types
#define IOinstant 1
#define IOinstantCycle 2
#define IOinterrupt 10

class IODriver {
public:
	IODriver();

	virtual void begin();
	virtual void cycle();

	virtual int readData(int address);
	virtual void writeData(int address, bool data);
	virtual void writeData(int address, int data);

private:
	
};

#endif