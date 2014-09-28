#include "Arduino.h"
#include "PID.h"

PID::PID() {}
PID::PID(AI **input, float min, float max, AO **output, float P, float I, float D) {
	_init(input, min, max, output, P, I, D, 1000.0, false);
}
PID::PID(AI **input, float min, float max, AO **output, float P, float I, float D, float deviationLimit) {
	_init(input, min, max, output, P, I, D, deviationLimit, false);
}
PID::PID(AI **input, float min, float max, AO **output, float P, float I, float D, float deviationLimit, bool fast) {
	_init(input, min, max, output, P, I, D, deviationLimit, fast);
}
void PID::_init(AI **input, float min, float max, AO **output, float P, float I, float D, float deviationLimit, bool fast) {
	_id = -1;
	
	_min = min;
	_max = max;

	_fast = fast;

	_deviationLimit = deviationLimit / 100.0;

	_P = P;
	_I = I;
	_D = D;
	
	_AI = *input;
	_AO = *output;
	
	_active = false;
}

void PID::setId(int id) {
	_id = id;
}

void PID::activate(bool activate) {
	_active = activate;
}
bool PID::isActive() {
	return _active;
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

void PID::begin(Time * time, Communication * communication, IO * io) {

}
void PID::loop(Time * time, Communication * communication, IO * io) {
	bool stateChanged = false;

	_value = _AI->value();

	if (_active) {
		if (time->t100ms || _fast) {
			if (!_wasActive) {
				_wasActive = stateChanged = true;
			}
			float error = _sp - _value;
			float prevError = error - _previousError;
			_previousError = error;

			_totalError = max(_min, min(_max, (_totalError + error)));

			float newOutput = _output + (error * _P) + (_totalError * _I) + (prevError * _D);

			_output = max(_min, min(_max, newOutput));	
		}
		if (abs(_sp - _value) >= (_max - _min) * _deviationLimit) {
			if (time->t1s)
				_deviated = ++_devDelay >= 5;

			if (_deviated && !_wasDeviated)
				stateChanged = _wasDeviated = true;
		}
		else {
			_deviated = false;
			
			stateChanged = stateChanged || _wasDeviated;
			_wasDeviated = false;

			_devDelay = 0;
		}
	}
	else {
		stateChanged = _wasActive;
		_wasActive = false;

		_output = 0.0;
	}

	if (time->t1s || stateChanged) {
		PIDsendStruct data;

		data.status.active = _active;
		data.status.deviated = _deviated;
		data.status.fast = _fast;

		data.input = _value;
		data.sp = _sp;
		data.output = _output;
		data.P = _P;
		data.I = _I;
		data.D = _D;
		data.deviationLimit = _deviationLimit;

		communication->sendData(sizeof(data), typePID, _id, (char *)&data);
	}

	_AO->output(_output);
	_AO->activate(_active);
}