#include "Arduino.h"
#include "IO.h"

IO::IO() {}
IO::IO(int driverCount) {
	_driverCount = driverCount;
	_filledSlot = -1;

	_drivers = new IODriver*[_driverCount];
	_pinLayout = new int[_driverCount];
}

void IO::registerDriver(int rangeLow, int rangeHigh, IODriver * driver) {
	if (_filledSlot > -1 && _pinLayout[_filledSlot] > rangeLow)
		return;

	_drivers[++_filledSlot] = driver;
	_pinLayout[_filledSlot] = rangeLow;
}

void IO::begin() {
	for (int i = _filledSlot; i >= 0; i--)
		_drivers[i]->begin();
}

// TODO: change this to only cycle-able drivers
void IO::cycle() {
	for (int i = _filledSlot; i >= 0; i--)
		_drivers[i]->cycle();
}

void IO::mode(int address, int mode) {
	for (int i = _filledSlot; i >= 0; i--) {
		if (address >= _pinLayout[i]) {
			return _drivers[i]->mode(address - _pinLayout[i], mode);
		}
	}
}

bool IO::digitalRead(int address) {
	for (int i = _filledSlot; i >= 0; i--) {
		if (address >= _pinLayout[i]) {
			return _drivers[i]->digitalRead(address - _pinLayout[i]);
		}
	}
}

void IO::digitalWrite(int address, bool data) {
	for (int i = _filledSlot; i >= 0; i--) {
		if (address >= _pinLayout[i]) {
			_drivers[i]->digitalWrite(address - _pinLayout[i], data);
			break;
		}
	}
}

int IO::analogRead(int address) {
	for (int i = _filledSlot; i >= 0; i--) {
		if (address >= _pinLayout[i]) {
			return _drivers[i]->analogRead(address - _pinLayout[i]);
		}
	}
}

void IO::analogWrite(int address, int data) {
	for (int i = _filledSlot; i >= 0; i--) {
		if (address >= _pinLayout[i]) {
			_drivers[i]->analogWrite(address - _pinLayout[i], data);
			break;
		}
	}
}