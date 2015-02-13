#include "Arduino.h"
#include "General.h"
#include "Communication.h"

int Communication::_remoteSubscriberId = 0;

Communication::Communication() {
	if (_remoteSubscriberId < 0) {
		_remoteSubscribers = new int[-(_remoteSubscriberId)];
	}
	
	started = false;
}

bool Communication::isOk() {
	return !!Serial;
}

void Communication::setup() {
	Serial.begin(115200);

	// TODO: handshake
	/*char * data = new char;
	char correctData = 0xAA;
	
	while (!started) {
		while (Serial.available()) {
			Serial.readBytes(data, 1);
			started = data[0] == correctData || started;
		}
		delay(1);
		if (started) {
			Serial.write(correctData);
		}
	}

	delay(1000);

	delete[] data;*/
}

void Communication::begin() {
}

void Communication::loop(General * general) {
	while (Serial.available() > 10) {
		CommunicationReceiveHeader * header = new CommunicationReceiveHeader();
		CommunicationFooter * footer = new CommunicationFooter();

		char * headerBuffer = new char[9];
		char * dataBuffer;
		char * footerBuffer = new char[1];

		Serial.readBytes(headerBuffer, 9);

		memcpy(header, &headerBuffer, 9);

		if (header->header == 0xAA) {

			Serial.readBytes(dataBuffer, min(9,header->payloadSize));
			Serial.readBytes(footerBuffer, 1);
		
			memcpy(footer, &footerBuffer, 9);

			if (footer->footer == 0x55) {
				if (header->communicationId < 0) {
					//general->getTypical(_remoteSubscribers[-(header->communicationId) - 1])->receiveData(header->payloadSize, dataBuffer);
				}
				else {
					// find object to send data //
				}
			}
		}
		Serial.flush();
		delete header, footer;
		delete[] headerBuffer, dataBuffer, footerBuffer;
	}
}

void Communication::sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload)
{
	sendData(payloadSize, comId, id, payload, _nodeAddress);
}
void Communication::sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload, unsigned char nodeAddress)
{
	CommunicationSendHeader header = CommunicationSendHeader(_localAddress, nodeAddress, payloadSize, comId, id);
	CommunicationFooter footer = CommunicationFooter();

	unsigned char * buffer = new unsigned char[(payloadSize + 10)];

	memcpy(buffer, &header, 9);
	memcpy(buffer + 9, payload, payloadSize);
	memcpy(buffer + (payloadSize + 9), &footer, 1);

	Serial.write(buffer, payloadSize + 10);

	delete[] buffer;
}

int Communication::remoteAddress(unsigned char sourceAddress, unsigned int comId, int id) {

	RemoteCommunication info = RemoteCommunication(--_remoteSubscriberId, sourceAddress, comId, id);

	unsigned char * buffer = new unsigned char[9];

	memcpy(buffer, &info, 9);

	Serial.write(buffer, 9);

	delete[] buffer;

	return _remoteSubscriberId;
}