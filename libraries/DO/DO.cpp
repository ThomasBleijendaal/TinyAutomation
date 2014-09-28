#include "Arduino.h"
#include "DO.h"

DO::DO() {}
DO::DO(int pin) {
	_pin = pin;

	_interlock = false;
	_active = false;
	_blinks = false;
	_wasActive = false;

	_startCount = 0U;
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

void DO::begin(Time * time, Communication * communication, IO * io) {
	io->mode(_pin, OUTPUT);
}
void DO::loop(Time * time, Communication * communication, IO * io) {
	bool stateChanged = false;

	if (_active) {
		if (!_blinks || (_blinks && time->b1s)) {
			io->digitalWrite(_pin, HIGH);
		}
		else if (_blinks && !time->b1s) {
			io->digitalWrite(_pin, LOW);
		}

		if (!_wasActive) {
			_startCount++;
			_wasActive = true;
			stateChanged = true;
		}
		if (time->t100ms) {
			_activeTime++;
		}
	}
	else {
		io->digitalWrite(_pin, LOW);

		stateChanged = _wasActive;
		_wasActive = false;
	}

	if (stateChanged || time->t1s) {
		DOdataStruct data;

		data.status.active = _active;
		data.status.interlock = _interlock;

		data.startCount = _startCount;
		data.activeTime = activeTime();

		communication->sendData(sizeof(data), typeDO, _id, (char*)&data);
	}
}