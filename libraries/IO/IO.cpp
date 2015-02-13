#include "Arduino.h"
#include "IO.h"

IO::IO() {}
IO::IO(int driverCount) {
	_driverCount = 0; 
	_cycleDriverCount = 0;
	_interruptDriverCount = 0;
}

// TODO: driver type
void IO::registerDriver(int rangeLow, int rangeHigh, IODriver * driver, int driverType) {
	int newId = _driverCount;

	if (_driverCount > 0 && _addressLow[_driverCount] > rangeLow)
		return;

	if (_driverCount > 0) {
		driver->baseDriver = _drivers[0];

		IODriver ** oldArray = new IODriver*[_driverCount];

		int * oldArrayL = new int[_driverCount];
		int * oldArrayH = new int[_driverCount];
		//int * oldArrayType = new int[(driverType == IOinstantCycle) ? _cycleDriverCount : _interruptDriverCount];

		for (int i = 0; i < _driverCount; i++) {
			oldArray[i] = _drivers[i];

			oldArrayL[i] = _addressLow[i];
			oldArrayH[i] = _addressHigh[i];

			//oldArrayType[i] = (driverType == IOinstantCycle) ? _cycleDrivers[i] : _interruptDrivers[i];
		}
		
		delete[] _drivers, _addressLow, _addressHigh;
		
		//if (driverType == IOinstantCycle) {
		//	delete[] _cycleDrivers;
		//}
		//else {
		//	delete[] _interruptDrivers;
		//}

		_drivers = new IODriver*[++_driverCount];

		_addressLow = new int[_driverCount];
		_addressHigh = new int[_driverCount];

		for (int i = 0; i < _driverCount; i++) {
			_drivers[i] = oldArray[i];

			_addressLow[i] = oldArrayL[i];
			_addressHigh[i] = oldArrayH[i];
		}

		delete[] oldArray, oldArrayL, oldArrayH;// , oldArrayType;
	}
	else {
		_drivers = new IODriver*[++_driverCount];

		_addressLow = new int[_driverCount];
		_addressHigh = new int[_driverCount];

		_cycleDrivers = new int[max(1,_cycleDriverCount)];
		_interruptDrivers = new int[max(1,_interruptDriverCount)];
	}

	if (driverType == IOinstantCycle) {
		++_cycleDriverCount;
	}
	else {
		++_interruptDriverCount;
	}

	_drivers[newId] = driver;
	_addressLow[newId] = rangeLow;
	_addressHigh[newId] = rangeHigh;

	if (driverType == IOinstantCycle) {
		_cycleDrivers[_cycleDriverCount] = newId;
	}
	else {
		_interruptDrivers[_interruptDriverCount] = newId;
	}
}

void IO::begin() {
	for (int i = 0; i < _driverCount; i++) {
		_drivers[i]->begin();
	}
}

void IO::cycle() {
	for (int i = 0; i < _cycleDriverCount; i++) {
		_drivers[_cycleDrivers[i]]->cycle();
	}
}

void IO::interrupt() {
	for (int i = 0; i < _interruptDriverCount; i++) {
		_drivers[_interruptDrivers[i]]->cycle();
	}
}

void IO::mode(int address, int mode) {
	for (int i = 0; i < _driverCount; i++) {
		if (address <= _addressHigh[i]) {
			_drivers[i]->mode(address - _addressLow[i], mode);
		}
	}
}

bool IO::digitalRead(int address) {
	for (int i = 0; i < _driverCount; i++) {
		if (address <= _addressHigh[i]) {
			return _drivers[i]->digitalRead(address - _addressLow[i]);
		}
	}
}

void IO::digitalWrite(int address, bool data) {
	for (int i = 0; i < _driverCount; i++) {
		if (address <= _addressHigh[i]) {
			_drivers[i]->digitalWrite(address - _addressLow[i], data);
			break;
		}
	}
}

int IO::analogRead(int address) {
	for (int i = 0; i < _driverCount; i++) {
		if (address <= _addressHigh[i]) {
			return _drivers[i]->analogRead(address - _addressLow[i]);
		}
	}
}

float IO::formattedRead(int address) {
	for (int i = 0; i < _driverCount; i++) {
		if (address <= _addressHigh[i]) {
			return _drivers[i]->formattedRead(address - _addressLow[i]);
		}
	}
}

void IO::analogWrite(int address, int data) {
	for (int i = 0; i < _driverCount; i++) {
		if (address <= _addressHigh[i]) {
			_drivers[i]->analogWrite(address - _addressLow[i], data);
			break;
		}
	}
}