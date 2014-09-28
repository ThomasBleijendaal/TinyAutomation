/*
Digital Input

Reads a digital input. Counts the times the input is turned on and the duration of the input being on.

*/
#ifndef DI_h
#define DI_h

#include <Typical.h>
#include <Time.h>
#include <Communication.h>
#include <IO.h>

// char, char, int, float =2h1f
struct DIdataStruct {
	struct status {
		bool active : 1;
		char spare : 7;
		status() {
			active = false;
			spare = 0;
		}
	} status;
	struct cmd {
		char spare : 8;
		cmd() {
			spare = 0;
		}
	} cmd;
	int switchCount;
	float activeTime;

	DIdataStruct() {
		switchCount = 0;
		activeTime = 0.0;
	}
};

class DI : public Typical {
public:
	DI();
	DI(int pin);
	DI(int pin, bool NC);

	bool isActive();
	bool activated();
	bool deActivated();

	unsigned int switchCount();
	float activeTime();

	void begin(Time * time, Communication * communication, IO * io);
	void loop(Time * time, Communication * communication, IO * io);
private:
	void _init(int pin, bool NC);

	int _pin;
	
	bool _NC;
	
	bool _active;
	bool _activated;
	bool _deActivated;

	unsigned int _switchCount;
	unsigned int _activeTime;
};

#endif