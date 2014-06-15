/*
Analog Input

Writes an analog output (PWM). Recieves a 0 - 100 % input which is converted to 0 - 255. Minimum and maximum output are in %. Rate of change is % / s.

*/
#ifndef AO_h
#define AO_h

#include <AO.h>
#include <General.h>

class AO {
public:
	AO(int pin);
	AO(int pin, float min, float max);
	AO(int pin, float min, float max, float rate);

	void output(float output);
	void activate(bool activate);

	float output();
	float average();
	float activeTime();
	float voltage();

	void interlock(bool i0, bool i1, bool i2);

	void loop(General &general);

private:
	void _init(int pin, float min, float max, float rate);

	int _pin;
	int _raw;

	bool _interlock;
	bool _active;

	float _output;
	float _currentOutput;

	float _avg;
	float _min;
	float _max;
	float _rate;

	unsigned int _activeTime;
};

#endif