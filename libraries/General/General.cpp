#include "Arduino.h"
#include "General.h"

General::General(int typicalCount, int deviceCount, int ioCount) {
	communication = Communication();
	time = Time();

	io = IO(ioCount);

	_typicals = new Typical*[typicalCount];
	_devices = new Device*[deviceCount];
	_typicalCount = 0;
	_deviceCount = 0;
}

void General::begin() {
	io.begin();

	time.loop();

	for (int i = 0; i < _typicalCount; i++) {
		_typicals[i]->begin(&time, &communication, &io);
	}

	for (int i = 0; i < _deviceCount; i++) {
		_devices[i]->begin(&time, &communication);
	}
}

void General::loop() {
	time.loop();

	communication.read();

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

	communication.send();
}

void General::_add(Typical * object) {
	_typicals[_typicalCount] = object;
	_typicals[_typicalCount]->setId(_typicalCount++);
}
void General::_add(Device * object) {
	_devices[_deviceCount] = object;
	_devices[_deviceCount]->setId(_deviceCount++);
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