/*
Digital Output

Writes a digitial output. Set the output according to its active state, counts the times the output is switched on and the time the output is on.

*/
#ifndef DO_h
#define DO_h

#include <Typical.h>
#include <Time.h>
#include <Communication.h>
#include <IO.h>

// char, char, int, float =2h1f
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

	DOdataStruct() {
		startCount = 0;
		activeTime = 0.0;
	}
};

class DO : public Typical {
public:
	DO();
	DO(int pin);

	bool isActive();
	unsigned int startCount();
	float activeTime();

	void activate(bool activate);
	void blink(bool blink);

	void interlock(bool i0, bool i1, bool i2);

	void begin(Time &time, Communication &communication, IO &io);
	void loop(Time &time, Communication &communication, IO &io);
private:
	int _pin;

	bool _interlock;
	bool _active;
	bool _blinks;
	bool _wasActive;

	unsigned int _startCount;
	unsigned int _activeTime;
};

#endif