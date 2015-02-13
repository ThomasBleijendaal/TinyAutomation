#include "Arduino.h"
#include "DI.h"

void DI::begin(Time * time, Communication * communication, IO * io) {
	io->mode(_address, (settings.NC) ? INPUT_PULLUP : INPUT);
}
void DI::loop(Time * time, Communication * communication, IO * io) {
	if (_address > 0) {
		bool pinValue = io->digitalRead(_address);

		status.activated = false;
		status.deActivated = false;

		if ((pinValue && !settings.NC) || (!pinValue && settings.NC)) {
			if (!status.active) {
				status.activated = true;
				data.switchCount++;
				status.active = true;
			}
			if (time->t100ms) {
				data.activeTime += 0.1;
			}
		}
		else {
			status.deActivated = status.active;
			status.active = false;
		}
	}

	if (status.activated || status.deActivated || time->t1s) {
		DI_commSend_t sendData;

		sendData.data = data;
		sendData.status = status;

		communication->sendData(sizeof(sendData), DI_COM_data_ID, _id, (char*)&sendData);
	}
}
void DI::receiveData(unsigned int payloadSize, const char * data) {
	// remote communicating
	if (_address < 0) {
		DI_commSend_t * buffer = new DI_commSend_t();

		memcpy(buffer, &data, payloadSize);

		this->data = buffer->data;
		this->status = buffer->status;

		delete[] buffer;
	}
	else {

	}
}