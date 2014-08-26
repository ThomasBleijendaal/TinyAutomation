#include "Arduino.h"
#include "AO.h"


AO::AO(int id, int pin) {
	_init(id, pin, 0.0, 100.0, -1.0);
}
AO::AO(int id, int pin, float min, float max) {
	_init(id, pin, min, max, -1.0);
}
AO::AO(int id, int pin, float min, float max, float rate) {
	_init(id, pin, min, max, rate);
}
void AO::_init(int id, int pin, float min, float max, float rate) {
	_id = id;
	_pin = pin;

	pinMode(_pin, OUTPUT);

	_min = min;
	_max = max;
	_rate = rate;

	_active = false;

	_raw = (int)(_min * 2.55);
	_output = 0.0;
	_currentOutput = min;

	analogWrite(_pin, _raw);
}

void AO::activate(bool activate) {
	_active = activate;
}

void AO::output(float output) {
	_output = output;
}

float AO::output() {
	if (_active) {
		return _currentOutput;
	}
	else{
		return 0.0;
	}
}
float AO::voltage() {
	return output() * (5.0 / 100.0);
}

float AO::average() {
	return _avg;
}

float AO::activeTime() {
	return ((float)_activeTime) / 10.0;
}

void AO::interlock(bool i0, bool i1, bool i2) {
	_interlock = i0 || i1 || i2;
	if (_interlock)
		_active = false;
}

void AO::loop(General &general) {
	int sp = max(_min, min(_max, _output));
	bool stateChanged = false;

	if (_active) {
		if (_rate != -1 && general.t100ms) {
			
			float delta = _rate / 10.0;

			if (sp > _currentOutput) {
				_currentOutput = min(sp, _currentOutput + delta);
			}
			else if (sp < _currentOutput) {
				_currentOutput = max(sp, _currentOutput - delta);
			}
		}
		else if (_rate == -1) {
			_currentOutput = max(_min, min(_max, _output));
		}

		if (general.t100ms) {
			_avg = ((_avg * 99.0) + _currentOutput) / 100.0;

			if (_active)
				_activeTime++;
		}

		analogWrite(_pin, (int)(_currentOutput * 2.55));

		if (!_wasActive) {
			_startCount++;
			stateChanged = true;
			_wasActive = true;
		}
	}
	else if (_wasActive) {
		stateChanged = true;
		_wasActive = false;

		_currentOutput = _min;

		analogWrite(_pin, 0);
	}
	
	if (stateChanged || general.t1s) {
		AOdataStruct data;

		data.status.active = _active;
		data.status.interlock = _interlock;

		data.startCount = _startCount;
		data.activeTime = activeTime();
		data.output = _currentOutput;

		general.stageSend(typeAO, _id, *((dataStruct *)&data));
	}
}