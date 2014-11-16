#include "Arduino.h"
#include "DO.h"

void DO::begin(Time * time, Communication * communication, IO * io) {
	io->mode(_address, OUTPUT);
}

void DO::loop(Time * time, Communication * communication, IO * io) {
	bool stateChanged = false;

	if (status.active) {
		io->digitalWrite(_address, true);

		if (status.wasActive) {
			data.startCount++;
			status.wasActive = true;
			stateChanged = true;
		}
		if (time->t100ms) {
			data.activeTime += 0.1;
		}
	}
	else {
		io->digitalWrite(_address, false);

		stateChanged = status.wasActive;
		status.wasActive = false;
	}

	if (stateChanged || time->t1s) {
		DO_commSend_t sendData;

		sendData.data = data;
		sendData.status = status;

		communication->sendData(sizeof(sendData), DO_COM_data_ID, _id, (char*)&sendData);
	}
}