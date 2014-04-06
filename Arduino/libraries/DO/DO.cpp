#include "Arduino.h"
#include "DO.h"

DO::DO(int pin) {
	pinMode(pin, OUTPUT);

	_pin = pin;

	_active = false;
	_wasActive = false;
	_switchCount = 0U;
	_activeTime = 0U;
}

void DO::activate(bool activate) {
	if (!_blinks)
		_active = activate;
}

void DO::blink(bool blink) {
	_active = blink;
	_blinks = blink;
}

bool DO::isActive() {
	return _active;
}

unsigned int DO::switchCount() {
	return _switchCount;
}

float DO::activeTime() {
	return ((float)_activeTime) / 10.0;
}

void DO::loop(bool t100ms, bool b1s) {
	if (_active) {
		if (!_blinks || (_blinks && b1s)) {
			digitalWrite(_pin, HIGH);
		}
		else if(_blinks && !b1s) {
			digitalWrite(_pin, LOW);
		}

		if (!_wasActive) {
			_switchCount++;
			_wasActive = true;
		}
		if (t100ms) {
			_activeTime++;
		}
	}
	else {
		digitalWrite(_pin, LOW);

		_wasActive = false;
	}
}