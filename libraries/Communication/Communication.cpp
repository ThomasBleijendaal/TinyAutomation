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
void Communication::stageSend(int type, int nr, dataStruct data) {
	commStruct newItem;

	newItem.type = type;
	newItem.nr = nr;
	newItem.data = data;

	char buffer[24];
	memcpy(buffer, &newItem, 24);

	Serial.write(buffer, 24);
}
