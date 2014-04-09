#include "Arduino.h"
#include "AI.h"

AI::AI(int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh) {
	_pin = pin;

	_rangeLow = rangeLow;
	_rangeHigh = rangeHigh;

	_rawLow = rawLow;
	_rawHigh = rawHigh;

	_lolo = lolo;
	_lo = lo;
	_hi = hi;
	_hihi = hihi;

	_enable = true;
	_enableLolo = (lolo > rangeLow);
	_enableLo = (lo > lolo);
	_enableHi = (hi < hihi);
	_enableHihi = (hihi < rangeHigh);
	_enableBTA = enableBTA;

	_raw = 0;
	_value = 0.0;

	_avg = 0.0;
	_min = rangeHigh;
	_max = rangeLow;

	_firstCycle = true;
}

void AI::loop(General &general) {
	if (_enable)
		_raw = analogRead(_pin);
	
	_value = ((float) (_raw - _rawLow)) * ((_rangeHigh - _rangeLow) / ((float) (_rawHigh - _rawLow))) + _rangeLow;

	if (_firstCycle) {
		_avg = _value;
		_min = _value;
		_max = _value;

		_firstCycle = false;
	}
	else {
		if (general.t100ms) {
			_avg = ((_avg * 99.0) + _value) / 100.0;
		}

		_min = min(_min, _value);
		_max = max(_max, _value);
	}

	float delta = (_rangeHigh - _rangeLow) * 0.01;

	_isLolo = _enableLolo && (_isLolo || _value < _lolo) && _value <= _lolo + delta;
	_isLo = _enableLo && (_isLo || _value < _lo) && _value <= _lo + delta;
	_isHi = _enableLolo && (_isHi || _value > _hi) && _value >= _hi - delta;
	_isHihi = _enableLolo && (_isHihi || _value > _hihi) && _value >= _hihi - delta;
	_isBTA = _enableBTA && (_isBTA || _value <= _rangeLow || _value >= _rangeHigh) && (_value <= _rangeLow + delta || _value >= _rangeHigh - delta);

}

void AI::enable(bool enable) { _enable = enable; }

float AI::rangeLow() { return _rangeLow; }
float AI::rangeHigh() { return _rangeHigh; }
float AI::value() { return _value; }
float AI::voltage() { return ((float)_raw) / (5.0 / 1024.0); }
float AI::average() { return _avg; }
float AI::minimum() { return _min; }
float AI::maximum() { return _max; }

bool AI::lolo() { return _isLolo; }
bool AI::lo() { return _isLo; }
bool AI::hi() { return _isHi; }
bool AI::hihi() { return _isHihi; }
bool AI::bta() { return _isBTA; }
