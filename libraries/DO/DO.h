/*
Digital Output

Writes a digitial output. Set the output according to its active state, counts the times the output is switched on and the time the output is on.

*/
#ifndef DO_h
#define DO_h

#include <Time.h>
#include <Communication.h>
#include <IO.h>

struct DOdataStruct {
	struct status {
		bool active : 1;
		bool interlock : 1;
		char spare : 6;
		status() {
			active = false;
			interlock = false;
			spare = 0;
		}
	} status;
	struct cmd {
		char spare : 8;
		cmd() {
			spare = 0;
		}
	} cmd;
	int startCount;
	float activeTime;
	char spare[8];

	DOdataStruct() {
		startCount = 0;
		activeTime = 0.0;
		spare[0] = 0;
		spare[1] = 0;
		spare[2] = 0;
		spare[3] = 0;
		spare[4] = 0;
		spare[5] = 0;
		spare[6] = 0;
		spare[7] = 0;
	}
};

class DO {
public:
	DO();
	DO(int pin);

	void setId(int id);
	
	bool isActive();
	unsigned int startCount();
	float activeTime();

	void activate(bool activate);
	void blink(bool blink);

	void interlock(bool i0, bool i1, bool i2);

	void loop(Time &time, Communication &communication, IO &io);
private:
	int _pin;
	int _id;

	bool _interlock;
	bool _active;
	bool _blinks;
	bool _wasActive;

	unsigned int _startCount;
	unsigned int _activeTime;
};

#endif