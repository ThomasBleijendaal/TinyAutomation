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
void Communication::sendData(int payloadSize, int type, int nr, const char * payload) 
{
	int header = 1234;
	unsigned int identifier = payloadSize * 1000 + type * 100 + nr;
	int footer = 4321;

	char * buffer = new char[(payloadSize + 6)];
	
	memcpy(buffer, &header, 2);
	memcpy(buffer + 2, &identifier, 2);
	memcpy(buffer + 4, payload, payloadSize);
	memcpy(buffer + (payloadSize + 4), &footer, 2);

#ifndef COMM_DEBUG
	for (int i = 0; i < (payloadSize + 6); i++)
		Serial.write(buffer[i]);
#else
	for (int i = 0; i < (payloadSize + 6); i++) {
		Serial.print(buffer[i],HEX);
		Serial.print(".");
	}
	Serial.println(payloadSize);
#endif
	

	delete[] buffer;

}
