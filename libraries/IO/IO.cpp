#include "Arduino.h"
#include "IO.h"

IO::IO() {}
IO::IO(int driverCount) {
	_driverCount = driverCount;
	_filledSlot = -1;

	_drivers = new IODriver*[_driverCount];
	_addressLow = new int[_driverCount];
	_addressHigh = new int[_driverCount];

	_cycleDrivers = new int[_driverCount];
	_interruptDrivers = new int[_driverCount];

	for (int i = 0; i < _driverCount; i++) {
		_addressLow[i] = 0;
		_addressHigh[i] = 0;
		_cycleDrivers[i] = 0;
		_interruptDrivers[i] = 0;
	}
}

void IO::registerDriver(int rangeLow, int rangeHigh, IODriver * driver, int driverType) {
	if (_filledSlot > -1 && _addressLow[_filledSlot] > rangeLow)
		return;

	_drivers[++_filledSlot] = driver;
	_addressLow[_filledSlot] = rangeLow;
	_addressHigh[_filledSlot] = rangeHigh;

	if (driverType == IOinstantCycle) {
		int i = -1;
		while (_cycleDrivers[++i] > 0) {}
		_cycleDrivers[i] = _filledSlot;
	}
	else if (driverType == IOinterrupt) {
		int i = -1;
		while (_interruptDrivers[++i] > 0) {}
		_interruptDrivers[i] = _filledSlot;
	}
}

void IO::begin() {
	for (int i = 0; i <= _filledSlot; i++) {
		_drivers[i]->begin();
	}
}

void IO::cycle() {
	int i = 0;

	while (_cycleDrivers[i] > 0) {
		_drivers[_cycleDrivers[i++]]->cycle();
	}
}

void IO::interrupt() {
	int i = 0;

	while (_interruptDrivers[i] > 0) {
		_drivers[_interruptDrivers[i++]]->cycle();
	}
}

void IO::mode(int address, int mode) {
	for (int i = 0; i <= _filledSlot; i++) {
		if (address <= _addressHigh[i]) {
			_drivers[i]->mode(address - _addressLow[i], mode);
		}
	}
}

bool IO::digitalRead(int address) {
	for (int i = 0; i <= _filledSlot; i++) {
		if (address <= _addressHigh[i]) {
			return _drivers[i]->digitalRead(address - _addressLow[i]);
		}
	}
}

void IO::digitalWrite(int address, bool data) {
	for (int i = 0; i <= _filledSlot; i++) {
		if (address <= _addressHigh[i]) {
			_drivers[i]->digitalWrite(address - _addressLow[i], data);
			break;
		}
	}
}

int IO::analogRead(int address) {
	for (int i = 0; i <= _filledSlot; i++) {
		if (address <= _addressHigh[i]) {
			return _drivers[i]->analogRead(address - _addressLow[i]);
		}
	}
}

void IO::analogWrite(int address, int data) {
	for (int i = 0; i <= _filledSlot; i++) {
		if (address <= _addressHigh[i]) {
			_drivers[i]->analogWrite(address - _addressLow[i], data);
			break;
		}
	}
}