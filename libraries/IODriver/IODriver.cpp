#include "Arduino.h"
#include "IODriver.h"

IODriver::IODriver() {}
void IODriver::begin() {}
void IODriver::cycle() {}

int IODriver::readData(int address) {}

void IODriver::writeData(int address, bool data) {}
void IODriver::writeData(int address, int data) {}