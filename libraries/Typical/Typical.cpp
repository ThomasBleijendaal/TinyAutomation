#include "Arduino.h"
#include "Typical.h"

void Typical::setId(int id) {
	_id = id;
}
void Typical::begin(Time * time, Communication * communication, IO * io) {}
void Typical::loop(Time * time, Communication * communication, IO * io) {}
void Typical::receiveData(unsigned int payloadSize, const char * data) {};