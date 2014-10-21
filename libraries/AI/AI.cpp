#include "Arduino.h"
#include "AI.h"

AI::AI() {}
AI::AI(int pin) {
	_pin = pin;

	_firstCycle = true;
	_firstValueSet = false;
}

void AI::begin(Time * time, Communication * communication, IO * io) {
	io->mode(_pin, INPUT);
}

void AI::loop(Time * time, Communication * communication, IO * io) {
	int raw;
	
	if (_pin != -1) {
		if (settings.enable)
			raw = io->analogRead(_pin);

		float value = ((float)(raw - settings.rawLow)) * ((settings.rangeHigh - settings.rangeLow) / ((float)(settings.rawHigh - settings.rawLow))) + settings.rangeLow;
		
		if (settings.damping)
			data.value = ((9.0 * data.value) + value) / 10.0;
		else
			data.value = value;
	}

	if (_firstCycle || (_pin == -1 && !_firstValueSet)) {
		data.avg = data.value;
		data.min = data.value;
		data.max = data.value;

		if (!(_pin == -1 && !_firstValueSet))
			_firstCycle = false;
	}
	else {
		data.min = min(data.min, data.value);
		data.max = max(data.max, data.value);

		float delta = (settings.rangeHigh - settings.rangeLow) * 0.01;

		status.isLolo = settings.enableLolo && (status.isLolo || data.value < settings.lolo) && data.value <= settings.lolo - delta;
		status.isLo = settings.enableLo && (status.isLo || data.value < settings.lo) && data.value <= settings.lo - delta;
		status.isHi = settings.enableHi && (status.isHi || data.value > settings.hi) && data.value >= settings.hi + delta;
		status.isHihi = settings.enableHihi && (status.isHihi || data.value > settings.hihi) && data.value >= settings.hihi + delta;
		status.isBTA = settings.enableBTA && (status.isBTA || data.value <= settings.rangeLow || data.value >= settings.rangeHigh) && (data.value <= settings.rangeLow + delta || data.value >= settings.rangeHigh - delta);

		if (time->t100ms) {
			data.avg = ((data.avg * 99.0) + data.value) / 100.0;
		}
		if (time->t1s) {
			AIdataStruct sendData;

			sendData.data = data;
			sendData.status = status;

			communication->sendData(sizeof(data), typeAI, _id, (char*)&sendData);
		}
	}
}
