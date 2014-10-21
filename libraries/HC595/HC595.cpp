#include "Arduino.h"
#include "HC595.h"

HC595::HC595(int dataPin, int clockPin, int latchPin, int chainLength) {
	_dataPin = dataPin;
	_clockPin = clockPin;
	_latchPin = latchPin;
	_chainLength = chainLength;
	
	_dataPinMask = 0x04; // digital_pin_to_bit_mask_PGM[dataPin]; // 0x01 << dataPin;
	_clockPinMask = 0x02; // digital_pin_to_bit_mask_PGM[clockPin]; // 0x01 << clockPin;
	_latchPinMask = 0x08; // digital_pin_to_bit_mask_PGM[latchPin]; // 0x01 << latchPin;

	_writeData = new bool[chainLength * 8];
	for (int i = 0; i < chainLength * 8; i++)
		_writeData[i] = false;
}

void HC595::begin() {
	baseDriver->mode(_dataPin, OUTPUT);
	baseDriver->mode(_clockPin, OUTPUT);
	baseDriver->mode(_latchPin, OUTPUT);

	baseDriver->digitalWrite(_latchPin, true);
}

void HC595::cycle() {
	if (!_writeRequired)
		return;
	
	_writeRequired = false;

	// don't interrupt in the write cycle //
	noInterrupts();

	baseDriver->digitalWrite(_latchPin, false);
	//PORTB &= (unsigned char)~_latchPinMask;

	for (int b = (_chainLength * 8) - 1; b >= 0; b--) {
		if (_writeData[b])
			baseDriver->digitalWrite(_dataPin, true);
		//PORTB |= _dataPinMask;
		else
			baseDriver->digitalWrite(_dataPin, false);
			//PORTB &= (unsigned char)~_dataPinMask;
		
		baseDriver->digitalWrite(_clockPin, true);
		//PORTB |= _clockPinMask;
		baseDriver->digitalWrite(_clockPin, false);
		//PORTB &= (unsigned char)~_clockPinMask;
	}

	baseDriver->digitalWrite(_latchPin, true);
	//PORTB |= _latchPinMask;

	interrupts();
}
void HC595::digitalWrite(int address, bool data) {
	_writeRequired = true;

	int byteNr = int(address / 8);
	int bitNr = int(address % 8);

	_writeData[(byteNr * 8) + bitNr] = data;
}