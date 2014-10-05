#include "Arduino.h"
#include "MCP3008.h"

MCP3008::MCP3008(int clock, int dataIn, int dataOut, int chipSelect) {
	// resuse those masks for the actual addresses for pinmode setting at setup-time
	_clockMask = (unsigned char)clock;
	_dataInMask = (unsigned char)dataIn;
	_dataOutMask = (unsigned char)dataOut;
	_chipSelectMask = (unsigned char)chipSelect;

	_port.clock = clock > 7;
	_port.dataIn = dataIn > 7;
	_port.dataOut = dataOut > 7;
	_port.chipSelect = chipSelect > 7;
}

void MCP3008::begin() {
	pinMode(_clockMask, OUTPUT);
	pinMode(_dataInMask, OUTPUT);
	pinMode(_dataOutMask, INPUT);
	pinMode(_chipSelectMask, OUTPUT);

	_dataInMask = 0x01 << _dataInMask % 8;
	_dataOutMask = 0x01 << _dataOutMask % 8;
	_clockMask = 0x01 << _clockMask % 8;
	_chipSelectMask = 0x01 << _chipSelectMask % 8;
}

int MCP3008::analogRead(int address) {
	int result = 0;
	
	if (_port.clock) PORTB |= _clockMask; else PORTD |= _clockMask;

	if (_port.chipSelect) PORTB |= _chipSelectMask; else PORTD |= _chipSelectMask;
	if (_port.chipSelect) PORTB &= ~_chipSelectMask; else PORTD &= ~_chipSelectMask;
	
	// START BIT
	if (_port.dataIn) PORTB |= _dataInMask; else PORTD |= _dataInMask;
	
	if (_port.clock) PORTB &= ~_clockMask; else PORTD &= ~_clockMask;
	if (_port.clock) PORTB |= _clockMask; else PORTD |= _clockMask;
	
	// SINGLE CHANNEL BIT
	// (dataIn still high) //
	if (_port.clock) PORTB &= ~_clockMask; else PORTD &= ~_clockMask;
	if (_port.clock) PORTB |= _clockMask; else PORTD |= _clockMask;
		
	// THREE ADDRESS BITS
	for (int i = 0; i < 3; i++) {
		if (address & 0x04)
			if (_port.dataIn) PORTB |= _dataInMask; else PORTD |= _dataInMask;
		else
			if (_port.dataIn) PORTB &= ~_dataInMask; else PORTD &= ~_dataInMask;
		
		if (_port.clock) PORTB &= ~_clockMask; else PORTD &= ~_clockMask;
		if (_port.clock) PORTB |= _clockMask; else PORTD |= _clockMask;
			
		address = address << 1;
	}

	// dataIn is done. //
	if (_port.dataIn) PORTB &= ~_dataInMask; else PORTD &= ~_dataInMask;

	// SAMPLE BIT
	if (_port.clock) PORTB &= ~_clockMask; else PORTD &= ~_clockMask;
	if (_port.clock) PORTB |= _clockMask; else PORTD |= _clockMask;

	// NULL BIT
	if (_port.clock) PORTB &= ~_clockMask; else PORTD &= ~_clockMask;
	if (_port.clock) PORTB |= _clockMask; else PORTD |= _clockMask;

	// 10 DATA BITS MSB
	for (int i = 9; i >= 0; i--) {
		if (_port.clock) PORTB &= ~_clockMask; else PORTD &= ~_clockMask;
		
		result |= ((_port.dataOut) ? bool(PINB & _dataOutMask) : bool(PIND & _dataOutMask)) << i;

		if (_port.clock) PORTB |= _clockMask; else PORTD |= _clockMask;
	}

	// Lower the clock and be done //
	if (_port.clock) PORTB &= ~_clockMask; else PORTD &= ~_clockMask;

	return result;
}