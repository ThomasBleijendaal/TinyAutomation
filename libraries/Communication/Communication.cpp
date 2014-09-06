#include "Arduino.h"
#include "Communication.h"

Communication::Communication() {
}

void Communication::send() {
}
void Communication::read() {
}

dataStruct Communication::readData(int type, int nr) {
	dataStruct nothing;
	return nothing;
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
	memcpy(buffer + 20, &footer, 2);

	for (int i = 0; i < (payloadSize + 6); i++)
		Serial.write(buffer[i]);

	delete[] buffer;

}
