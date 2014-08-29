#include "Arduino.h"
#include "Time.h"

Time::Time() {
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
}
	
void Time::loop() {
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
