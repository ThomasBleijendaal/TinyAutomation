#include "Arduino.h"
#include "HC595.h"

HC595::HC595(int dataPin, int clockPin, int latchPin, int chainLength) {
	_dataPin = dataPin;
	_clockPin = clockPin;
	_latchPin = latchPin;
	_chainLength = chainLength;
	
	_dataPinMask = 0x01 << dataPin;
	_clockPinMask = 0x01 << clockPin;
	_latchPinMask = 0x01 << latchPin;

	_writeData = new bool[chainLength * 8];
	for (int i = 0; i < chainLength * 8; i++)
		_writeData[i] = false;
}

void HC595::begin() {
	
	pinMode(_dataPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);

	PORTD |= _latchPinMask;
}

void HC595::cycle() {
	if (!_writeRequired)
		return;

	_writeRequired = false;

	// don't interrupt in the write cycle //
	noInterrupts();

	PORTD &= (unsigned char)~_latchPinMask;

	for (int b = (_chainLength * 8) - 1; b >= 0; b--) {
		if (_writeData[b])
			PORTD |= _dataPinMask;
		else
			PORTD &= (unsigned char)~_dataPinMask;

		PORTD |= _clockPinMask;
		PORTD &= (unsigned char)~_clockPinMask;
	}

	PORTD |= _latchPinMask;

	interrupts();
}
void HC595::digitalWrite(int address, bool data) {
	_writeRequired = true;

	int byteNr = int(address / 8);
	int bitNr = int(address % 8);

	_writeData[(byteNr * 8) + bitNr] = data;
}