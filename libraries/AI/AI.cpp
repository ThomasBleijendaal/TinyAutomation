#include "Arduino.h"
#include "AI.h"

void AI::begin(Time * time, Communication * communication, IO * io) {
	io->mode(_address, INPUT);
}

void AI::loop(Time * time, Communication * communication, IO * io) {
	if (settings.enable) {
		if(settings.useFormatted) {
			data.value = io->formattedRead(_address);
		}
		else if(!settings.useExternalValue) {
			data.value = ((float)(io->analogRead(_address) - settings.rawLow)) * ((settings.rangeHigh - settings.rangeLow) / ((float)(settings.rawHigh - settings.rawLow))) + settings.rangeLow;
		}

		if (_firstCycle) {
			data.avg = data.value;
			data.minValue = data.value;
			data.maxValue = data.value;
		}
		else {
			data.minValue = min(data.minValue, data.value);
			data.maxValue = max(data.maxValue, data.value);

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
				AI_commSend_t sendData;

				sendData.data = data;
				sendData.status = status;

				communication->sendData(sizeof(sendData), AI_COM_data_ID, _id, (char*)&sendData);
			}
		}
	}
}
