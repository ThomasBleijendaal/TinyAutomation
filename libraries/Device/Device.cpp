#include "Arduino.h"
#include "Device.h"

void Device::setId(int id) {
	_id = id;
}
void Device::begin(Time * time, Communication * communication) {}
void Device::loop(Time * time, Communication * communication) {}