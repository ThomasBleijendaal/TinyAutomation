#include "Arduino.h"
#include "ATmega32u4.h"

ATmega32u4::ATmega32u4() {}
void ATmega32u4::begin() {}
void ATmega32u4::cycle() {}

void ATmega32u4::mode(int address, int mode) {
	pinMode(address, mode);
}

bool ATmega32u4::digitalRead(int address) {
//#ifndef FASTDIGITAL
	return (::digitalRead(address) == HIGH);
//#else
//	if (address > 7) {
//		return bool(PINB & (0x01 << address - 8));
//	}
//	else {
//		return bool(PIND & (0x01 << address));
//	}
//#endif
}
void ATmega32u4::digitalWrite(int address, bool data) {
//#ifndef FASTDIGITAL
	::digitalWrite(address, data);
//#else
//	if (address > 7) {
//		if (data) {
//			PORTB |= (0x01 << address - 8);
//		}
//		else {
//			PORTB &= ~(0x01 << address - 8);
//		}
//	}
//	else {
//		if (data) {
//			PORTD |= (0x01 << address);
//		}
//		else {
//			PORTD &= ~(0x01 << address);
//		}
//	}
//#endif
}

int ATmega32u4::analogRead(int address) {
	return ::analogRead(address);
}
void ATmega32u4::analogWrite(int address, int data) {
	::analogWrite(address, data);
}