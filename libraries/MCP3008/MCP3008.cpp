#include "Arduino.h"
#include "MCP3008.h"

MCP3008::MCP3008(int resampleCount, int delayTime, int CLK, int Din, int Dout, int ChipSelect) {
	_resampleCount = resampleCount;
	_delayTime = delayTime;

	_CLK = CLK;
	_Din = Din;
	_Dout = Dout;
	_CS = ChipSelect;
}

void MCP3008::begin() {
	pinMode(_CLK, OUTPUT);
	pinMode(_Din, OUTPUT);
	pinMode(_Dout, INPUT);
	pinMode(_CS, OUTPUT);

	digitalWrite(_CLK, HIGH);
	digitalWrite(_Din, LOW);
	digitalWrite(_CS, LOW);
}

int MCP3008::analogRead(int address) {
	int data = 0;
	int result = 0;

	for (int r = 0; r < _resampleCount; r++) {
		digitalWrite(_Din, LOW);
		digitalWrite(_CLK, HIGH);

		digitalWrite(_CS, HIGH);
		delayMicroseconds(_delayTime);
		digitalWrite(_CS, LOW);
		
		digitalWrite(_Din, HIGH);
		
		digitalWrite(_CLK, LOW);
		delayMicroseconds(_delayTime);
		digitalWrite(_CLK, HIGH);
		
		digitalWrite(_Din, HIGH);
		
		digitalWrite(_CLK, LOW);
		delayMicroseconds(_delayTime);
		digitalWrite(_CLK, HIGH);
		
		// 3 selection bits
		for (int i = 0; i < 3; i++) {
			digitalWrite(_Din, (address & 0x04) ? HIGH : LOW);
			delayMicroseconds(_delayTime);
			digitalWrite(_CLK, LOW);
			delayMicroseconds(_delayTime);
			digitalWrite(_CLK, HIGH);
			
			address = address << 1;
		}

		digitalWrite(_CLK, LOW);
		delayMicroseconds(_delayTime);
		digitalWrite(_CLK, HIGH);
		
		// 10 CLK cycles Dout
		for (int i = 0; i < 10; i++) {
			digitalWrite(_CLK, LOW);
			delayMicroseconds(_delayTime);
			
			data |= digitalRead(_Dout) << (10 - i);

			digitalWrite(_CLK, HIGH);
			delayMicroseconds(_delayTime);
		}

		digitalWrite(_CLK, HIGH);
		digitalWrite(_Din, LOW);

		result += data;
	}


	return int(result / _resampleCount);


}