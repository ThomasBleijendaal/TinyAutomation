#include "Arduino.h"
#include "Communication.h"

int Communication::_RemoteSubscriberId = 0;

Communication::Communication() {
	started = false;
}

void Communication::setup() {
	Serial.begin(115200);

	char * data = new char[1];
	char correctData = 0xAA;
	
	while (!started) {
		while (Serial.available()) {
			Serial.readBytes(data, 1);
			started = data[0] == correctData || started;
		}
		delay(10);
		if (started) {
			Serial.write(correctData);
		}
	}

	delete[] data;
}

void Communication::begin() {
	
}

void Communication::loop() {

}

void Communication::sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload)
{
	sendData(payloadSize, comId, id, payload, _nodeAddress);
}
void Communication::sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload, unsigned char nodeAddress)
{
	CommunicationHeader header = CommunicationHeader(_localAddress, nodeAddress, payloadSize, comId, id);
	CommunicationFooter footer = CommunicationFooter();

	unsigned char * buffer = new unsigned char[(payloadSize + sizeof(header) + sizeof(footer))];

	memcpy(buffer, &header, 9);
	memcpy(buffer + 9, payload, payloadSize);
	memcpy(buffer + (payloadSize + 9), &footer, 2);

	Serial.write(buffer, payloadSize + 11);

	delete[] buffer;
}

int Communication::remoteAddress(unsigned char sourceAddress, unsigned int comId, int id) {

	RemoteCommunication info = RemoteCommunication(--_RemoteSubscriberId, sourceAddress, comId, id);

	unsigned char * buffer = new unsigned char[(sizeof(info))];

	memcpy(buffer, &info, 0);

	Serial.write(buffer, sizeof(buffer));

	delete[] buffer;

	return _RemoteSubscriberId;
}