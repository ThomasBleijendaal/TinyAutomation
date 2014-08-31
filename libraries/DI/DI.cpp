#include "Arduino.h"
#include "DI.h"
#include "General.h"

DI::DI() {}
DI::DI(int pin) {
	_init(pin, false);
}
DI::DI(int pin, bool NC) {
	_init(pin, NC);
}
void DI::_init(int pin, bool NC) {
	pinMode(_pin, (NC) ? INPUT_PULLUP : INPUT);
	
	_id = -1;
	_pin = pin;
	_NC = NC;

	_active = false;
	_switchCount = 0U;
	_activeTime = 0U;
}

void DI::setId(int id) {
	_id = id;
}

bool DI::isActive() {
	return _active;
}
bool DI::activated() {
	return _activated;
}
bool DI::deActivated() {
	return _deActivated;
}

unsigned int DI::switchCount() {
	return _switchCount;
}

float DI::activeTime() {
	return float(_activeTime) / 10.0;
}

void DI::loop(Time &time, Communication &communication) {
	int pinValue = digitalRead(_pin);

	_activated = false;
	_deActivated = false;

	if (((pinValue == HIGH && !_NC) || (pinValue == LOW && _NC))) {
		if (!_active) {
			_activated = true;
			_switchCount++;
			_active = true;
		}
		if (time.t100ms) {
			_activeTime++;
		}
	}
	else {
		_deActivated = _active;
		_active = false;
	}

	if (_activated || _deActivated || time.t1s) {
		DIdataStruct data;

		data.status.active = _active;

		data.switchCount = _switchCount;
		data.activeTime = activeTime();

		communication.sendData(typeDI, _id, *((dataStruct *)&data));
	}
}