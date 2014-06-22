#include "Arduino.h"
#include "DI.h"

DI::DI(int pin) {
	_init(pin, false);
}
DI::DI(int pin, bool NC) {
	_init(pin, NC);
}
void DI::_init(int pin, bool NC) {
	if (NC) {
		pinMode(_pin, INPUT_PULLUP);
	}
	else
	{
		pinMode(_pin, INPUT);
	}
	_pin = pin;
	_NC = NC;

	_active = false;
	_switchCount = 0U;
	_activeTime = 0U;
}

void DI::simulate(bool activate) {
	_simulation = activate;
}

void DI::simulation(bool activate) {
	_simulationActive = activate;
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
	return ((float) _activeTime) / 10.0;
}

void DI::loop(General &general) {
	int pinValue = digitalRead(_pin);
	_activated = false;
	_deActivated = false;

	if (((pinValue == HIGH && !_NC) || (pinValue == LOW && _NC)) || (_simulation && _simulationActive)) {
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

	if (_activated || _deActivated)
		general.stageSend(1,0,short((_active) ? 1 : 0),0.0,0.0,0.0);
}

void DI::recieveData(short cmd, float data1, float data2, float data3) {
	
}