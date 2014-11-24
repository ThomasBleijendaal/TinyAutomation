#include "Arduino.h"
#include "Communication.h"

Communication::Communication() {
}

void Communication::send() {
}
void Communication::read() {
}

char * Communication::readData(int type, int nr) {
	char * buffer = new char[10];
	return buffer;
}
void Communication::sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload)
{
	sendData(payloadSize, comId, id, payload, _remoteAddress);
}
void Communication::sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload, unsigned char remoteAddress)
{
	CommunicationHeader header = CommunicationHeader(_address, remoteAddress, payloadSize, comId, id);
	CommunicationFooter footer = CommunicationFooter();

	unsigned char * buffer = new unsigned char[(payloadSize + sizeof(header) + sizeof(footer))];

	memcpy(buffer, &header, 6);
	memcpy(buffer + 6, payload, payloadSize);
	memcpy(buffer + (payloadSize + 6), &footer, 2);

#ifndef COMM_DEBUG
	Serial.write(buffer, payloadSize + 8);
#else
	for (int i = 0; i < (payloadSize + 8); i++) {
		Serial.print((unsigned char) buffer[i],HEX);
		Serial.print(".");
	}
	Serial.print("....");
	Serial.println(payloadSize);
#endif
	

	delete[] buffer;
}
