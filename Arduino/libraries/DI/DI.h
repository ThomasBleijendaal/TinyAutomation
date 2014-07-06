/*
Digital Input

Reads a digital input. Counts the times the input is turned on and the duration of the input being on.

*/
#ifndef DI_h
#define DI_h

#include <DI.h>
#include <General.h>

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
	char spare[8];

	DIdataStruct() {
		switchCount = 0;
		activeTime = 100.0;
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
class DI {
public:
	DI(int id, int pin);
	DI(int id, int pin, bool NC);

	bool isActive();
	bool activated();
	bool deActivated();

	unsigned int switchCount();
	float activeTime();
		
	void loop(General &general);
private:
	void _init(int id, int pin, bool NC);

	int _pin;
	int _id;
	
	bool _NC;
		
	bool _active;
	bool _activated;
	bool _deActivated;

	unsigned int _switchCount;
	unsigned int _activeTime;
};

#endif