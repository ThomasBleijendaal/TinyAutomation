#include "Arduino.h"
#include "General.h"

Application * General::_app;
extern General general;

// default Arduino functions
void setup()
{
	general.setup();
}

void loop()
{
	general.loop();
}

General::General(int typicalCount, int deviceCount, int ioCount) {
	communication = Communication();
	time = Time();

	io = IO(ioCount);

	_typicalCount = 0;
	_deviceCount = 0;

	_communicationLost = false;
	_canContinueWithoutCommunication = false;
}

void General::setProgram(Application * app) {
	_app = app; 
}

void General::setup() {
	communication.setup();

	_app->setup();

	io.begin();
	communication.begin();

	time.loop();

	for (int i = 0; i < _typicalCount; i++) {
		_typicals[i]->begin(&time, &communication, &io);
	}

	for (int i = 0; i < _deviceCount; i++) {
		_devices[i]->begin(&time, &communication);
	}

	_app->onStart();
}

void General::loop() {
	if (!_communicationLost && !communication.isOk()) {
		_communicationLost = true;

		_canContinueWithoutCommunication = _app->onSerialError();
	}
	else if (_communicationLost && communication.isOk()) {
		_communicationLost = false;
		_canContinueWithoutCommunication = false;

		_app->onStart();
	}

	if (!_communicationLost || _canContinueWithoutCommunication) {
		time.loop();
		communication.loop(this);

		_app->loop();


		for (int i = 0; i < _typicalCount; i++) {
			_typicals[i]->loop(&time, &communication, &io);
		}

		for (int i = 0; i < _deviceCount; i++) {
			_devices[i]->loop(&time, &communication);
		}

		if (time.t5s) {
			io.interrupt();
		}
		else {
			io.cycle();
		}
	}
}

Typical * General::getTypical(int id) {
	return _typicals[id];
}

void General::_add(Typical * object) {
	int newId = _typicalCount;

	// expand array
	if (_typicalCount > 0) {
		Typical ** oldArray = new Typical*[_typicalCount];
		for (int i = 0; i < _typicalCount; i++) {
			oldArray[i] = _typicals[i];
		}
		delete[] _typicals;

		_typicals = new Typical*[++_typicalCount];

		for (int i = 0; i < _typicalCount - 1; i++) {
			_typicals[i] = oldArray[i];
		}

		delete[] oldArray;
	}
	else {
		_typicals = new Typical*[++_typicalCount];
	}

	// append new object
	_typicals[newId] = object;
	_typicals[newId]->setId(newId);
}
void General::_add(Device * object) {
	int newId = _deviceCount;

	// expand array
	if (_deviceCount > 0) {
		Device ** oldArray = new Device*[_deviceCount];
		for (int i = 0; i < _deviceCount; i++) {
			oldArray[i] = _devices[i];
		}
		delete[] _devices;

		_devices = new Device*[++_deviceCount];

		for (int i = 0; i < _deviceCount - 1; i++) {
			_devices[i] = oldArray[i];
		}

		delete[] oldArray;
	}
	else {
		_devices = new Device*[++_deviceCount];
	}

	// append new object
	_devices[newId] = object;
	_devices[newId]->setId(newId);
}

template <>
AI * General::add<AI>(AI * object) { _add(object); return object; }
template <>
AO * General::add<AO>(AO * object) { _add(object); return object; }
template <>
DI * General::add<DI>(DI * object) { _add(object); return object; }
template <>
DO * General::add<DO>(DO * object) { _add(object); return object; }
//template <>
//M * General::add<M>(M * object) { _add(object); return object; }
template <>
PID * General::add<PID>(PID * object) { _add(object); return object; }

template <class T>
T * General::add(T * object) {
	_add(object);
	return object;
}