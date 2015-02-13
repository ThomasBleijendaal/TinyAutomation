#include "Arduino.h"
#include "ATmega328.h"

ATmega328::ATmega328() {}
void ATmega328::begin() {}
void ATmega328::cycle() {}

void ATmega328::mode(int address, int mode) {
	// only modify the digital pins
	if (address < A0)
		pinMode(address, mode);
}

bool ATmega328::digitalRead(int address) {
#ifndef FASTDIGITAL
	return (::digitalRead(address) == HIGH);
#else
	if (address > 7) {
		return bool(PINB & (0x01 << address - 8));
	}
	else {
		return bool(PIND & (0x01 << address));
	}
#endif
}
void ATmega328::digitalWrite(int address, bool data) {
#ifndef FASTDIGITAL
	::digitalWrite(address, data);
#else
	if (address > 7) {
		if (data) {
			PORTB |= (0x01 << address - 8);
		}
		else {
			PORTB &= ~(0x01 << address - 8);
		}
	}
	else {
		if (data) {
			PORTD |= (0x01 << address);
		}
		else {
			PORTD &= ~(0x01 << address);
		}
	}
#endif
}

int ATmega328::analogRead(int address) {
	return ::analogRead(address);
}
void ATmega328::analogWrite(int address, int data) {
	::analogWrite(address, data);
}