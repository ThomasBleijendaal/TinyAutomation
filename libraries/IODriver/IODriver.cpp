#include "Arduino.h"
#include "IODriver.h"

IODriver::IODriver() {}
void IODriver::begin() {}
void IODriver::cycle() {}
void IODriver::mode(int address, int mode) {}

bool IODriver::digitalRead(int address) {}
void IODriver::digitalWrite(int address, bool data) {}

int IODriver::analogRead(int address) {}
void IODriver::analogWrite(int address, int data) {}