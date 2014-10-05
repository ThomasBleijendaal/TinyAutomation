#include "Arduino.h"
#include "Wire.h"
#include "MCP23016.h"

void printr(int data) {
	for (int i = 15; i >= 0; i--) {
		Serial.print((data & (0x0001 << i)) ? "1" : "0");
	}
	Serial.println(" ");
}

MCP23016::MCP23016(int address) {
	_address = 0x20 | ((unsigned char)address & 0xff);

	_modes.data = 0xFFFF;
	_inputPolarity.data = 0x0000;

	_send.modesLo = true;
	_send.modesHi = true;

	_send.inputPolarityLo = true;
	_send.inputPolarityHi = true;

}

void MCP23016::begin() {
	// cycle at the beginning as the configuration is required to be send to the chip //
	// otherwise the program starts at the first loop writing to input addresses, or vice versa //
	cycle();
}

void MCP23016::cycle() {
	while (_send.all != 0) {
		Wire.beginTransmission(_address);

		if (_send.modesLo) {
			Wire.write(DIR0);
			Wire.write(_modes.bytes.lo);

			_send.modesLo = false;
		}
		else if (_send.modesHi) {
			Wire.write(DIR1);
			Wire.write(_modes.bytes.hi);

			_send.modesHi = false;
		}
		else if (_send.inputPolarityLo) {
			Wire.write(POL0);
			Wire.write(_inputPolarity.bytes.lo);

			_send.inputPolarityLo = false;
		}
		else if (_send.inputPolarityHi) {
			Wire.write(POL1);
			Wire.write(_inputPolarity.bytes.hi);

			_send.inputPolarityHi = false;
		}
		else if (_send.writesLo) {
			Wire.write(GP0);
			Wire.write(_write.bytes.lo);

			_send.writesLo = false;
		}
		else if (_send.writesHi) {
			Wire.write(GP1);
			Wire.write(_write.bytes.hi);

			_send.writesHi = false;
		}
		Wire.endTransmission();
	}

	Wire.beginTransmission(_address);
	Wire.write(GP0);
	Wire.endTransmission();
	Wire.requestFrom(_address, (unsigned char)0x01);

	while (Wire.available() < 1);

	if (Wire.available() == 1) {
		_read.bytes.lo = Wire.read();
	}
	Wire.beginTransmission(_address);
	Wire.write(GP1);
	Wire.endTransmission();
	Wire.requestFrom(_address, (unsigned char)0x01);

	while (Wire.available() < 1);

	if (Wire.available() == 1) {
		_read.bytes.hi = Wire.read();
	}
}
void MCP23016::mode(int address, int mode) {
	if (mode == INPUT) {
		_modes.data |= (0x0001 << address);
		_inputPolarity.data &= ~(0x0001 << address);
	}
	else if (mode == OUTPUT) {
		_modes.data &= ~(0x0001 << address);
	}
	else if (mode == INPUT_PULLUP) {
		_modes.data |= (0x0001 << address);
		_inputPolarity.data |= (0x0001 << address);
	}

	if (address > 7) {
		_send.modesHi = true;
		_send.inputPolarityHi = true;
	}
	else {
		_send.modesLo = true;
		_send.inputPolarityLo = true;
	}
}

bool MCP23016::digitalRead(int address) {
	return (_read.data & (0x0001 << address));
}

void MCP23016::digitalWrite(int address, bool data) {
	if (!data) {
		_write.data |= (0x0001 << address);
	}
	else {
		_write.data &= ~(0x0001 << address);
	}

	if (address > 7) {
		_send.writesHi = true;
	}
	else {
		_send.writesLo = true;
	}
}