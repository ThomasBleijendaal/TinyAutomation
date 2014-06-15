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
	return _active && _wasActive;
}

unsigned int DO::switchCount() {
	return _switchCount;
}

float DO::activeTime() {
	return ((float)_activeTime) / 10.0;
}

void DO::interlock(bool i0, bool i1, bool i2) {
	_interlock = i0 || i1 || i2;
	if (_interlock) {
		_active = false;
		_blinks = false;
	}
}

void DO::loop(General &general, IO &io) {
	if (_active) {
		if (!_blinks || (_blinks && general.b1s)) {
			io.writeBit(_pin, HIGH);
		}
		else if (_blinks && !general.b1s) {
			io.writeBit(_pin, LOW);
		}

		if (!_wasActive) {
			_switchCount++;
			_wasActive = true;
		}
		if (general.t100ms) {
			_activeTime++;
		}
	}
	else {
		io.writeBit(_pin, LOW);

		_wasActive = false;
	}
}