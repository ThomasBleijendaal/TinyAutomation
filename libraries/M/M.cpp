#include "Arduino.h"
#include "M.h"

M::M() {
	_active = false;
	_maxPins = 0;
	_seq = 0;
	_wasActive = false;
	_startCount = 0U;
	_activeTime = 0U;
	_id = -1;
}

void M::setId(int id) {
	_id = id;
}

void M::singleCoil(int pin0, int pin1) {
	_maxPins = 2;
	_pin[0] = pin0;
	_pin[1] = pin1;
}

void M::doubleCoil(int pin0, int pin1, int pin2, int pin3) {
	_maxPins = 4;
	_pin[0] = pin0;
	_pin[1] = pin1;
	_pin[2] = pin2;
	_pin[3] = pin3;
}

void M::activate(bool act, bool reverse) {
	_active = act;
	_reverse = act && reverse;
}
void M::activate(bool act) {
	activate(act, false);
}

void M::interlock(bool i0, bool i1, bool i2, bool i3, bool i4, bool i5) {
	_interlock1 = i0 || i1 || i2;
	if (_interlock1 && !_reverse)
		_active = false;

	_interlock2 = i3 || i4 || i5;
	if (_interlock2 && _reverse)
		_active = false;
}
void M::interlock(bool i0, bool i1, bool i2) {
	_interlock1 = i0 || i1 || i2;
	if (_interlock1)
		_active = false;
}

bool M::isActive() {
	return _active && _wasActive;
}

unsigned int M::startCount() {
	return _startCount;
}

float M::activeTime() {
	return ((float)_activeTime) / 10.0;
}

void M::loop(Time &time, Communication &communication, IO &io) {
	bool stateChanged = false;

	if (_active) {
		if (time.t2_5ms) {
			if (!_reverse) {
				_seq = (_seq + 1) % _maxPins;
			}
			else {
				_seq = (_maxPins + (_seq - 1)) % _maxPins;
			}
		}
		if (!_wasActive) {
			_startCount++;
			stateChanged = true;
			_wasActive = true;
		}
		if (time.t100ms) {
			_activeTime++;
		}
	}
	else {
		_seq = -1;
		stateChanged = _wasActive;
		_wasActive = false;
	}

	if (stateChanged || time.t1s) {
		MdataStruct data;

		data.status.active = _active;
		data.status.reverse = _reverse && _active;
		data.status.interlock = _interlock1;
		data.status.interlockReverse = _interlock2;

		data.startCount = _startCount;
		data.activeTime = activeTime();

		communication.sendData(typeM, _id, *((dataStruct *)&data));
	}

	for (int i = 0; i < _maxPins; ++i) {
		io.writeBit(_pin[i], _seq == i);
	}
}