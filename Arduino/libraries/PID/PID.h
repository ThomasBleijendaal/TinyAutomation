/*
PID controller

Basic implementation of a very naive PID controller.

*/
#ifndef PID_h
#define PID_h

#include <PID.h>
#include <General.h>

class PID {
public:
	PID(int AI, float min, float max, int AO, float P, float I, float D);
	PID(int AI, float min, float max, int AO, float P, float I, float D, float deviationLimit);
	PID(int AI, float min, float max, int AO, float P, float I, float D, float deviationLimit, bool fast);

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
	void _init(int AI, float min, float max, int AO, float P, float I, float D, float deviationLimit, bool fast);

	float _min;
	float _max;

	bool _fast;

	float _deviationLimit;
	bool _deviated;
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
};

#endif