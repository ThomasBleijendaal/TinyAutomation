#include "Arduino.h"
#include "Communication.h"

Communication::Communication() {
	//_sendBufferI = -1;
	//_readBufferI = -1;
}

void Communication::send() {
	/*while (_sendBufferI >= 0) {
		char buffer[20];

		memcpy(buffer, &_sendBuffer[_sendBufferI--], 20);

		Serial.write(buffer, 20);

		//commStruct empty;
		//_sendBuffer[_sendBufferI--] = empty;
	}*/
}
void Communication::read() {
	//char buffer[20];
	//commStruct readItem;

//	if (Serial.available() > 0)
	//	Serial.readBytes(buffer, 20);

//	memcpy(&readItem, buffer, 20);

	//_readBuffer[0] = readItem;
}

dataStruct Communication::readData(int type, int nr) {
	dataStruct nothing;
	return nothing;
}
void Communication::stageSend(int type, int nr, dataStruct data) {
	//if (_sendBufferI > 9)
	//	return;

	commStruct newItem;

	newItem.type = type;
	newItem.nr = nr;
	newItem.data = data;

	char buffer[24];
	memcpy(buffer, &newItem, 24);

	Serial.write(buffer, 24);
	
	//_sendBuffer[++_sendBufferI] = newItem;
}
