#include "Arduino.h"
#include "DO.h"
#include "General.h"
#include "IO.h"

DO::DO() {}
DO::DO(int pin) {
	pinMode(pin, OUTPUT);

	_id = -1;
	_pin = pin;

	_active = false;
	_wasActive = false;
	_startCount = 0U;
	_activeTime = 0U;
}

void DO::setId(int id) {
	_id = id;
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

unsigned int DO::startCount() {
	return _startCount;
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

void DO::loop(Time &time, Communication &communication, IO &io) {
	bool stateChanged = false;

	if (_active) {
		if (!_blinks || (_blinks && time.b1s)) {
			io.writeBit(_pin, HIGH);
		}
		else if (_blinks && !time.b1s) {
			io.writeBit(_pin, LOW);
		}

		if (!_wasActive) {
			_startCount++;
			_wasActive = true;
			stateChanged = true;
		}
		if (time.t100ms) {
			_activeTime++;
		}
	}
	else {
		io.writeBit(_pin, LOW);

		stateChanged = _wasActive;
		_wasActive = false;
	}

	if (stateChanged || time.t1s) {
		DOdataStruct data;

		data.status.active = _active;
		data.status.interlock = _interlock;

		data.startCount = _startCount;
		data.activeTime = activeTime();

		communication.stageSend(typeDO, _id, *((dataStruct *)&data));
	}
}