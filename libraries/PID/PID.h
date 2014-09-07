/*
PID controller

Basic implementation of a very naive PID controller.

*/
#ifndef PID_h
#define PID_h

#include <Time.h>
#include <Communication.h>
#include <AI.h>
#include <AO.h>

// char, char, float =1h1f
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

	PIDdataStruct() {
		sp = 0.0;
	}
};

class PID {
public:
	PID();
	PID(AI *input, float min, float max, AO *output, float P, float I, float D);
	PID(AI *input, float min, float max, AO *output, float P, float I, float D, float deviationLimit);
	PID(AI *input, float min, float max, AO *output, float P, float I, float D, float deviationLimit, bool fast);

	void setId(int id);

	float sp();

	bool isActive();
	bool isDeviated();

	void sp(float sp);
	void activate(bool activate);

	void loop(Time &time, Communication &communication);

private:
	void _init(AI *input, float min, float max, AO *output, float P, float I, float D, float deviationLimit, bool fast);

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

	AI *_AI;
	AO *_AO;

	float _value;
	float _totalError;
	float _previousError;

	float _output;

	float _sp;

	bool _active;
	bool _wasActive;
};

#endif