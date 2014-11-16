/*
Device layer

The device class provides a programming interface for more complex operations which require fast control or highly interruptive activities.

Various devices are foreseen:
- Interactive devices
	These devices use two or more Typicals and interact with them. For example, a PID controller, which intracts with an input and controls an output.
- Interruptive devices
	These devices use various inputs and outputs in order to control something which required very precise object, for example a stepper motor, until a specific requirement has been met.

*/
#ifndef Device_h
#define Device_h

#include <Time.h>
#include <Communication.h>

class Device {
public:
	Device() {};

	void setId(int id);

	virtual void begin(Time * time, Communication * communication);
	virtual void loop(Time * time, Communication * communication);

protected:
	int _id;
};

#endif