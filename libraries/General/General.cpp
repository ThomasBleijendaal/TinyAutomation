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

	//_sendBufferI = -1;
	//_readBufferI = -1;
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
	/*while (_sendBufferI >= 0) {
		char buffer[20];

		memcpy(buffer, &_sendBuffer[_sendBufferI--], 20);

		Serial.write(buffer, 20);

		//commStruct empty;
		//_sendBuffer[_sendBufferI--] = empty;
	}*/
}
void General::read() {
	//char buffer[20];
	//commStruct readItem;

//	if (Serial.available() > 0)
	//	Serial.readBytes(buffer, 20);

//	memcpy(&readItem, buffer, 20);

	//_readBuffer[0] = readItem;
}

dataStruct General::readData(int type, int nr) {
	dataStruct nothing;
	return nothing;
}
void General::stageSend(int type, int nr, dataStruct data) {
	//if (_sendBufferI > 9)
	//	return;

	commStruct newItem;

	newItem.type = type;
	newItem.nr = nr;
	newItem.data = data;

	char buffer[24];
	memcpy(buffer, &newItem, 24);

	Serial.write(buffer, 24);
	
	//_sendBuffer[++_sendBufferI] = newItem;
}