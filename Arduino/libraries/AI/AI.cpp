#include "Arduino.h"
#include "AI.h"

AI::AI(int id, int pin) {
	_init(id, pin, 0.0, 100.0, -1.0, -1.0, 101.0, 101.0, false, 0, 1023);
}
AI::AI(int id, int pin, float rangeLow, float rangeHigh) {
	_init(id, pin, rangeLow, rangeHigh, rangeLow - 1.0, rangeLow - 1.0, rangeHigh + 1.0, rangeHigh + 1.0, false, 0, 1023);
}
AI::AI(int id, int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi) {
	_init(id, pin, rangeLow, rangeHigh, lolo, lo, hi, hihi, false, 0, 1023);
}
AI::AI(int id, int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh) {
	_init(id, pin, rangeLow, rangeHigh, lolo, lo, hi, hihi, enableBTA, rawLow, rawHigh);
}

void AI::_init(int id, int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh) {
	_id = id;
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
	_firstValueSet = false;
}

void AI::loop(General &general) {
	if (_pin != -1) {
		if (_enable)
			_raw = analogRead(_pin);

		_value = ((float)(_raw - _rawLow)) * ((_rangeHigh - _rangeLow) / ((float)(_rawHigh - _rawLow))) + _rangeLow;
	}

	if (_firstCycle || (_pin == -1 && !_firstValueSet)) {
		_avg = _value;
		_min = _value;
		_max = _value;

		if (!(_pin == -1 && !_firstValueSet))
			_firstCycle = false;
	}
	else {
		_min = min(_min, _value);
		_max = max(_max, _value);

		float delta = (_rangeHigh - _rangeLow) * 0.01;

		_isLolo = _enableLolo && (_isLolo || _value < _lolo) && _value <= _lolo + delta;
		_isLo = _enableLo && (_isLo || _value < _lo) && _value <= _lo + delta;
		_isHi = _enableHi && (_isHi || _value > _hi) && _value >= _hi - delta;
		_isHihi = _enableHihi && (_isHihi || _value > _hihi) && _value >= _hihi - delta;
		_isBTA = _enableBTA && (_isBTA || _value <= _rangeLow || _value >= _rangeHigh) && (_value <= _rangeLow + delta || _value >= _rangeHigh - delta);

		if (general.t100ms) {
			_avg = ((_avg * 99.0) + _value) / 100.0;
		}
		if (general.t250ms) {
			AIdataStruct data;

			data.status.lolo = _isLolo;
			data.status.lo = _isLo;
			data.status.hi = _isHi;
			data.status.hihi = _isHihi;
			data.status.bta = _isBTA;

			data.value = _value;
			data.min = _min;
			data.max = _max;

			general.stageSend(2, _id, *((dataStruct *)&data));
		}
	}
}

void AI::enable(bool enable) { _enable = enable; }

void AI::setValue(float value) { if (_pin == -1) { _value = max(_rangeLow, min(_rangeHigh, value)); _firstValueSet = true; } }

float AI::rangeLow() { return _rangeLow; }
float AI::rangeHigh() { return _rangeHigh; }
float AI::value() { return _value; }
float AI::voltage() { return ((float)_raw) * (5.0 / 1023.0); }
float AI::average() { return _avg; }
float AI::minimum() { return _min; }
float AI::maximum() { return _max; }

bool AI::lolo() { return _isLolo; }
bool AI::lo() { return _isLo; }
bool AI::hi() { return _isHi; }
bool AI::hihi() { return _isHihi; }
bool AI::bta() { return _isBTA; }
