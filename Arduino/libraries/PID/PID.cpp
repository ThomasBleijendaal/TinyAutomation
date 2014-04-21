#include "Arduino.h"
#include "PID.h"

PID::PID(float min, float max, int AI, int AO) {
	_min = min;
	_max = max;

	_AI = AI;
	_AO = AO;
	
	_active = false;
}

void PID::activate(bool activate) {
	_active = activate;
}
bool PID::isActive() {
	return _active;
}

void PID::value(float value) {
	_value = value;
}
float PID::value() {
	return _value;
}

float PID::output() {
	return _output;
}

int PID::AI() {
	return _AI;
}
int PID::AO() {
	return _AO;
}

void PID::sp(float sp) {
	_sp = sp;
}
float PID::sp() {
	return _sp;
}

void PID::loop(General &general) {
	if (_active) {
		if (general.t100ms) {
			float delta = _sp - _value;
			float rDelta = 100.0 * delta / (_max - _min);
			float newOutput = _output + (rDelta / 10.0);

			_output = max(_min, min(_max, newOutput));
		}
	}
	else {
		_output = 0.0;
	}
}