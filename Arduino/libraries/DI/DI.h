/*
Digital Input

Reads a digital input. Counts the times the input is turned on and the duration of the input being on.

*/
#ifndef DI_h
#define DI_h

#include <DI.h>

class DI {
public:
	DI(int pin, bool NC);

	bool isActive();
	bool activated();
	bool deActivated();

	unsigned int switchCount();
	float activeTime();
		
	void simulate(bool activate);
	void simulation(bool activate);

	void loop(bool t100ms, bool b1s);
private:
	int _pin;
	
	bool _NC;
		
	bool _active;
	bool _activated;
	bool _deActivated;

	bool _simulation;
	bool _simulationActive;

	unsigned int _switchCount;
	unsigned int _activeTime;
};

#endif