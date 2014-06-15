#include "Arduino.h"
#include "PID.h"

PID::PID(int AI, float min, float max, int AO, float P, float I, float D) {
	_init(AI, min, max, AO, P, I, D, 0.0, false);
}
PID::PID(int AI, float min, float max, int AO, float P, float I, float D, float deviationLimit) {
	_init(AI, min, max, AO, P, I, D, deviationLimit, false);
}
PID::PID(int AI, float min, float max, int AO, float P, float I, float D, float deviationLimit, bool fast) {
	_init(AI, min, max, AO, P, I, D, deviationLimit, fast);
}
void PID::_init(int AI, float min, float max, int AO, float P, float I, float D, float deviationLimit, bool fast) {
	_min = min;
	_max = max;

	_fast = fast;

	_deviationLimit = deviationLimit / 100.0;

	_P = P;
	_I = I;
	_D = D;
	
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

bool PID::isDeviated() {
	return _deviated;
}

void PID::loop(General &general) {
	if (_active) {
		if (general.t100ms || _fast) {
			float error = _sp - _value;
			float prevError = error - _previousError;
			_previousError = error;

			_totalError = max(_min, min(_max, (_totalError + error)));

			float newOutput = _output + (error * _P) + (_totalError * _I) + (prevError * _D);

			_output = max(_min, min(_max, newOutput));	
		}
		if (abs(_sp - _value) >= (_max - _min) * _deviationLimit) {
			if (general.t1s)
				_deviated = ++_devDelay >= 5;
		}
		else {
			_deviated = false;
			_devDelay = 0;
		}
	}
	else {
		_output = 0.0;
	}
}