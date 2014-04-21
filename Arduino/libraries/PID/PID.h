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
	PID(float min, float max, int AI, int AO);

	float value();
	void value(float value);

	float output();
	float sp();

	int AI();
	int AO();

	bool isActive();

	void sp(float sp);
	void activate(bool activate);

	void loop(General &general);

private:
	float _min;
	float _max;

	int _AI;
	int _AO;

	float _value;
	float _output;

	float _sp;

	bool _active;
};

#endif