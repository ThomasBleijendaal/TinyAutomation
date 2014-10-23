#include "Arduino.h"
#include "AO.h"

void AO::begin(Time * time, Communication * communication, IO * io) {
	io->mode(_address, OUTPUT);
}

void AO::loop(Time * time, Communication * communication, IO * io) {
	int sp = max(data.minOutput, min(data.maxOutput, data.output));
	bool stateChanged = false;

	if(status.interlock) {
		status.active = false;
	}

	if (status.active) {
		if (data.rateOfChange != -1 && sp != data.currentOutput && time->t100ms) {

			float delta = data.rateOfChange / 10.0;

			if (sp > data.currentOutput) {
				data.currentOutput = min(sp, data.currentOutput + delta);
			}
			else if (sp < data.currentOutput) {
				data.currentOutput = max(sp, data.currentOutput - delta);
			}
		}
		else if (data.rateOfChange == -1) {
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

		data.currentOutput = data.minOutput;

		io->analogWrite(_address, 0);
	}

	if (stateChanged || time->t1s) {
		AO_commSend_t sendData;

		sendData.data = data;
		sendData.status = status;

		communication->sendData(sizeof(sendData), typeAO, _id, (char*)&sendData);
	}
}