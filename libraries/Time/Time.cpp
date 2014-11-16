#include "Arduino.h"
#include "Time.h"

void Time::loop() {
	unsigned long u = micros();

	++_cps;

	_resetTimers();

	if (t10ms = (u - 9999U > _ms) || (_ms + 9999U < u)) {
		_ms = u;

		t100ms = !(_1000ms++ % 10);
		_customTimer++;

		if(t1s = ++_1000ms == 100) {
			_1000ms = 0;

			if(++_m == 60) {
				_m = 0;
				t1m = true;

				t5s = !(_m % 5);
				t30s = !(_m % 30);

				if(++_h == 60) {
					_h = 0;
					t1h = true;

					t5m = !(_h % 5);
				}
			}
		}
	}
}

bool Time::timer(unsigned int ms) {
	return !(_customTimer % (int)((ms / 10)));
}

inline void Time::_resetTimers() {
	t10ms = false;
	t100ms = false;
	t1s = false;
	t5s = false;
	t30s = false;
	t1m = false;
	t5m = false;
	t1h = false;
}