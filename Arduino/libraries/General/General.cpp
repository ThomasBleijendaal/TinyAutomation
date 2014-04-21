#include "Arduino.h"
#include "General.h"

General::General() {
	t100ms = false;
	_t100ms = 0U;

	t250ms = false;
	_t250ms = 0U;
	
	t1s = false;
	b1s = false;
	_t1s = 0U;
	
	t5s = false;
	_t5s = 0U;

	t1m = false;
	_t1m = 0U;

	t5m = false;
	_t5m = 0U;

	cyclicLoad = 0;
	_cps = 10000;
}
void General::time() {
    unsigned int t100ms_new = millis();
    unsigned int t250ms_new = millis();
    unsigned int t1s_new = millis();
    unsigned int t5s_new = millis();

	_cps++;

    t100ms = (max(t100ms_new,_t100ms) - min(t100ms_new,_t100ms)) > 100U;
    if(t100ms) {
		_t100ms = t100ms_new;
	}

    t250ms = (max(t250ms_new,_t250ms) - min(t250ms_new,_t250ms)) > 250U;
    if(t250ms) { 
		_t250ms = t250ms_new;
	}
    
	t1s = (max(t1s_new,_t1s) - min(t1s_new,_t1s)) > 1000U;
    if(t1s) { 
		_t1s = t1s_new;
		b1s = !b1s;

		// 10 cycles per second = 100% load: the minimum at which the typicals may run //
		cyclicLoad = 1000.0 / _cps;
		_cps = 0;
	}
    
	t5s = (max(t5s_new,_t5s) - min(t5s_new,_t5s)) > 5000U;
    if(t5s) { 
		_t5s = t5s_new;
	}

	if (t1s)
		_t1m += 1U;
	t1m = _t1m == 60U;
	if (t1m)
		_t1m = 0U;
	
	if (t1s)
		_t5m += 1U;
	t5m = _t5m == 300U;
	if (t5m)
		_t5m = 0U;
}
