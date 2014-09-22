#include "Arduino.h"
#include "ATmega328.h"

ATmega328::ATmega328() {}
void ATmega328::begin() {}
void ATmega328::cycle() {}

void ATmega328::mode(int address, int mode) {
	// only modify the digital pins
	if (address < 20)
		pinMode(address, mode);
}

bool ATmega328::digitalRead(int address) {
	return digitalRead(address);
}
void ATmega328::digitalWrite(int address, bool data) {
	digitalWrite(address, data);
}

int ATmega328::analogRead(int address) {
	return analogRead(address - 20);
}
void ATmega328::analogWrite(int address, int data) {
	analogWrite(address - 20, data);
}