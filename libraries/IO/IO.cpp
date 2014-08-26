#include "Arduino.h"
#include "IO.h"

IO::IO() {

}

void IO::setRegisterOut(int dataWritePin, int clockPin, int latchPin, int writeBytes) {
	_dataWritePin = dataWritePin;
	_writeBytes = writeBytes;
	_clockPin = clockPin;
	_latchPin = latchPin;

	_dataWritePinMask = 0x01 << dataWritePin;
	_clockPinMask = 0x01 << clockPin;
	_latchPinMask = 0x01 << latchPin;

	pinMode(dataWritePin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);

	PORTD |= _latchPinMask;
}

void IO::writeBit(int pin, bool value) {
	if (pin < 100) {
		digitalWrite(pin, value);
	}
	else {
		int byteNr = ((int)(pin / 100)) - 1;
		int bitNr = pin % 100;

		_writeData[(byteNr * 8) + bitNr] = value;
	}
}

void IO::writeByte(int byte, unsigned char value) {
	for (int i = 0; i < 8; i++)
		_writeData[byte * 8 + i] = bitRead(value, i);
}

void IO::write() {
	PORTD &= (unsigned char)~_latchPinMask;

	for (int b = (_writeBytes * 8) - 1; b >= 0; b--) {
		if (_writeData[b])
			PORTD |= _dataWritePinMask;
		else
			PORTD &= (unsigned char)~_dataWritePinMask;

		PORTD |= _clockPinMask;
		PORTD &= (unsigned char)~_clockPinMask;
	}

	PORTD |= _latchPinMask;
}