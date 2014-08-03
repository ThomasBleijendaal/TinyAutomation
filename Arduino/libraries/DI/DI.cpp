#include "Arduino.h"
#include "DI.h"

DI::DI(int id,int pin) {
	_init(id, pin, false);
}
DI::DI(int id,int pin, bool NC) {
	_init(id, pin, NC);
}
void DI::_init(int id, int pin, bool NC) {
	if (NC) {
		pinMode(_pin, INPUT_PULLUP);
	}
	else
	{
		pinMode(_pin, INPUT);
	}
	_id = id;
	_pin = pin;
	_NC = NC;

	_active = false;
	_switchCount = 0U;
	_activeTime = 0U;
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

void DI::loop(General &general) {
	int pinValue = digitalRead(_pin);

	_activated = false;
	_deActivated = false;

	if (((pinValue == HIGH && !_NC) || (pinValue == LOW && _NC))) {
		if (!_active) {
			_activated = true;
			_switchCount++;
			_active = true;
		}
		if (general.t100ms) {
			_activeTime++;
		}
	}
	else {
		if (_active)
		{
			_deActivated = true;
		}
		_active = false;
	}

	if (_activated || _deActivated || general.t1s) {
		DIdataStruct data;

		data.status.active = _active;

		data.switchCount = _switchCount;
		data.activeTime = activeTime();

		general.stageSend(typeDI, _id, *((dataStruct *)&data));
	}
}