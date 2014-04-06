/*
Analog Input

Writes an analog output (PWM). Recieves a 0 - 100 % input which is converted to 0 - 255. Minimum and maximum output are in %. Rate of change is % / s.

*/
#ifndef AO_h
#define AO_h

#include <AO.h>

class AO {
public:
	AO(int pin, float min, float max, float rate);

	void output(float output);
	void activate(bool activate);

	float average();
	float activeTime();

	void loop(bool t100ms, bool b1s);

private:
	int _pin;
	int _raw;

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