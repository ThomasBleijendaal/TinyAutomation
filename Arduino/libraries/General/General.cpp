#include "Arduino.h"
#include "General.h"

General::General() {
	t2_5ms = false;
	_t2_5ms = micros();

	t100ms = false;
	_t100ms = 0;

	t250ms = false;
	_t250ms = 0;
	
	t1s = false;
	b1s = false;
	_t1s = 0;
	
	t5s = false;
	_t5s = 0;

	t1m = false;
	_t1m = 0;

	t5m = false;
	_t5m = 0;

	cps = 0;
	_cps = 0;

	_customTimer[0] = 0;
	_customTimer[1] = 0;
	_customTimer[2] = 0;
}
void General::time() {
	unsigned long u = micros();

	++_cps;

	t100ms = false;
	t250ms = false;
	t1s = false;
	t5s = false;
	t1m = false;
	t5m = false;

	t2_5ms = u - _t2_5ms >= 2500U;
	if (t2_5ms || u < _t2_5ms) {
		_t2_5ms = u;

		int id = -1;
		while (_customTimer[++id] > 0)
			_customTimerActive[id] = ++_customTimerCounter[id] == _customTimer[id];

		t100ms = ++_t100ms == 40;
		if (t100ms) {
			_t100ms = 0;

			t1s = ++_t1s == 10;
			if (t1s) {
				_t1s = 0;
				b1s = !b1s;

				cps = _cps;
				_cps = 0;

				t5s = ++_t5s == 5;
				if (t5s)
					_t5s = 0;

				t1m = ++_t1m == 60;
				if (t1m)
					_t1m = 0;

				t5m = ++_t5m == 300;
				if (t5m)
					_t5m = 0;
			}
		}

		t250ms = ++_t250ms > 100;
		if (t250ms)
			_t250ms = 0;
	}
}

void General::send() {
	if (_send) {
		char buffer[18];
		memcpy(buffer, &_sendBuffer[0], 18);

		Serial.write(buffer, 18);

		_send = false;
	}
}
void General::read() {
	//char buffer[18];

//	if (Serial.available() > 0)
	//	Serial.readBytes(buffer, 18);
	
//	memcpy(&readBuffer, buffer, 18);
}
void General::stageSend(int type, int nr, short status, float data1, float data2, float data3) {
	dataSend newItem;
	newItem.type = type;
	newItem.nr = nr;
	newItem.status = status;
	newItem.data1 = data1;
	newItem.data2 = data2;
	newItem.data3 = data3;

	_sendBuffer[0] = newItem;
	_send = true;
}


int General::registerTimer(int millis) {
	int id = -1;

	while (_customTimer[++id] != 0) {
		if (id == 3)
			return -1;
	}

	_customTimer[id] = int(float(millis) / 2.5);

	return id;
}
bool General::timer(int id) {
	return _customTimerActive[id % 3] && _t2_5ms;
}
