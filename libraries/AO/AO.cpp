#include "Arduino.h"
#include "AO.h"

void AO::begin(Time * time, Communication * communication, IO * io) {
	io->mode(_address, OUTPUT);

	data.output = settings.minOutput;
}

void AO::loop(Time * time, Communication * communication, IO * io) {
	float sp = max(settings.minOutput, min(settings.maxOutput, data.output));
	bool stateChanged = false;

	if(status.interlock) {
		status.active = false;
	}

	if (status.active) {
		if (settings.rateOfChange != -1.0 && sp != data.currentOutput && time->t100ms) {

			float delta = settings.rateOfChange / 10.0;

			if (sp > data.currentOutput) {
				data.currentOutput = min(sp, data.currentOutput + delta);
			}
			else if (sp < data.currentOutput) {
				data.currentOutput = max(sp, data.currentOutput - delta);
			}
		}
		else if (settings.rateOfChange == -1.0) {
			data.currentOutput = sp;
		}

		if (time->t100ms) {
			data.avg = ((data.avg * 99.0) + data.currentOutput) / 100.0;

			if (status.active) {
				data.activeTime += 0.1;
			}
		}

		io->analogWrite(_address, (int)(data.currentOutput * 2.55));

		if (!status.wasActive) {
			data.startCount++;
			stateChanged = true;
			status.wasActive = true;
		}
	}
	else if (status.wasActive) {
		stateChanged = true;
		status.wasActive = false;

		data.currentOutput = settings.minOutput;

		io->analogWrite(_address, 0);
	}

	if (stateChanged || time->t1s) {
		AO_commSend_t sendData;

		sendData.data = data;
		sendData.status = status;

		communication->sendData(sizeof(sendData), AO_COM_data_ID, _id, (char*)&sendData);
	}
}