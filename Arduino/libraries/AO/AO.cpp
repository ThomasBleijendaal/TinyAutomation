#include "Arduino.h"
#include "AO.h"

AO::AO(int pin, float min, float max, float rate) {
	pinMode(_pin, OUTPUT);

	_pin = pin;

	_min = min;
	_max = max;
	_rate = rate;

	_active = false;

	_raw = (int)(_min * 2.55);
	_output = 0.0;
	_currentOutput = 0.0;

	analogWrite(_pin, _raw);
}

void AO::activate(bool activate) {
	_active = activate;
}

void AO::output(float output) {
	_output = output;
}

float AO::average() {
	return _avg;
}

float AO::activeTime() {
	return ((float)_activeTime) / 10.0;
}

void AO::loop(bool t100ms, bool b1s) {
	int sp = max(_min, min(_max, _output));

	if (_active) {
		if (_rate != -1 && t100ms) {
			
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

		if (t100ms) {
			_avg = ((_avg * 99.0) + _currentOutput) / 100.0;

			if (_active)
				_activeTime++;
		}

	}
	else{
		_currentOutput = 0.0;
	}
	
	analogWrite(_pin, (int)(_currentOutput * 2.55));

}