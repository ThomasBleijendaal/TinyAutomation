/*
PID controller

Basic implementation of a very naive PID controller.

*/
#ifndef PID_h
#define PID_h

#include <PID.h>
#include <General.h>

struct PIDdataStruct {
	struct status {
		bool active : 1;
		bool deviated : 1;
		bool fast : 1;
		char spare : 5;
		status() {
			active = false;
			deviated = false;
			fast = false;
			spare = 0;
		}
	} status;
	struct cmd {
		char spare : 8;
		cmd() {
			spare = 0;
		}
	} cmd;
	float sp;
	char spare[10];

	PIDdataStruct() {
		sp = 0.0;
		spare[0] = 0;
		spare[1] = 0;
		spare[2] = 0;
		spare[3] = 0;
		spare[4] = 0;
		spare[5] = 0;
		spare[6] = 0;
		spare[7] = 0;
		spare[8] = 0;
		spare[9] = 0;
	}
};

class PID {
public:
	PID(int id, int AI, float min, float max, int AO, float P, float I, float D);
	PID(int id, int AI, float min, float max, int AO, float P, float I, float D, float deviationLimit);
	PID(int id, int AI, float min, float max, int AO, float P, float I, float D, float deviationLimit, bool fast);

	float value();
	void value(float value);

	float output();
	float sp();

	int AI();
	int AO();

	bool isActive();
	bool isDeviated();

	void sp(float sp);
	void activate(bool activate);

	void loop(General &general);

private:
	void _init(int id, int AI, float min, float max, int AO, float P, float I, float D, float deviationLimit, bool fast);

	int _id;

	float _min;
	float _max;

	bool _fast;

	float _deviationLimit;
	bool _deviated;
	bool _wasDeviated;
	int _devDelay;

	float _P;
	float _I;
	float _D;

	int _AI;
	int _AO;

	float _value;
	float _totalError;
	float _previousError;

	float _output;

	float _sp;

	bool _active;
	bool _wasActive;
};

#endif