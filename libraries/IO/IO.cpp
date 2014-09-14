#include "Arduino.h"
#include "IO.h"

IO::IO() {}
IO::IO(int driverCount) {
	_driverCount = driverCount + 1;
	_filledSlot = -1;

	_drivers = new IODriver*[_driverCount];
	_pinLayout = new int[_driverCount];

	registerDriver(0, 13, new DefaultDriver());
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

void IO::digitalWrite(int address, bool data) {
	for (int i = _filledSlot; i >= 0; i--) {
		if (address >= _pinLayout[i]) {
			_drivers[i]->writeData(address - _pinLayout[i], data);
			break;
		}
	}
}

int IO::analogRead(int address) {
	for (int i = _filledSlot; i >= 0; i--) {
		if (address >= _pinLayout[i]) {
			return _drivers[i]->readData(address - _pinLayout[i]);
		}
	}
}

void IO::analogWrite(int address, int data) {
	for (int i = _filledSlot; i >= 0; i--) {
		if (address >= _pinLayout[i]) {
			_drivers[i]->writeData(address - _pinLayout[i], data);
			break;
		}
	}
}

DefaultDriver::DefaultDriver() {}
void DefaultDriver::begin() {}
void DefaultDriver::cycle() {}

int DefaultDriver::readData(int address) {
	return analogRead(address);
}
void DefaultDriver::writeData(int address, bool data) {
	digitalWrite(address, data);
}
void DefaultDriver::writeData(int address, int data) {
	analogWrite(address, data);
}