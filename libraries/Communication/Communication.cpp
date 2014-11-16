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
void Communication::sendData(unsigned int payloadSize, unsigned int type, int id, const char * payload)
{
	unsigned int header = 0xAAAA;
	int identifier = lowByte(payloadSize) + lowByte(type) * 256;
	unsigned int footer = 0x5555;

	unsigned char * buffer = new unsigned char[(payloadSize + 8)];
	int i = 0;
	for (i = 0; i < payloadSize + 8; i++)
		buffer[i] = 0;
	
	memcpy(buffer, &header, 2);
	memcpy(buffer + 2, &identifier, 2);
	memcpy(buffer + 4, &id, 2);
	memcpy(buffer + 6, payload, payloadSize);
	memcpy(buffer + (payloadSize + 6), &footer, 2);

#ifndef COMM_DEBUG
	for (int i = 0; i < (payloadSize + 6); i++)
		Serial.write(buffer[i]);
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
