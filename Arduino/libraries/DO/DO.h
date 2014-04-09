/*
Digital Output

Writes a digitial output. Set the output according to its active state, counts the times the output is switched on and the time the output is on.

*/
#ifndef DO_h
#define DO_h

#include <DO.h>
#include <General.h>

class DO {
public:
	DO(int pin);
	
	bool isActive();
	unsigned int switchCount();
	float activeTime();

	void activate(bool activate);
	void blink(bool blink);

	void loop(General &general);
private:
	int _pin;

	bool _active;
	bool _blinks;
	bool _wasActive;

	unsigned int _switchCount;
	unsigned int _activeTime;
};

#endif