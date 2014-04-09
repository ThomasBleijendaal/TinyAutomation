/*
Analog Input

Reads an analog input. Maps the raw input to the configured range and determines if the input is out of range (bta, broken transmitter), 
too high (hihi), high (hi), low (lo) or too low (lolo). Also computes a rolling average per 100ms.

TODO:

allow partial range (eg. 600 - 900 instead of 0 - 1023)

*/
#ifndef AI_h
#define AI_h

#include <AI.h>
#include <General.h>

class AI {
public:
	AI(int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh);

	bool lolo();
	bool lo();
	bool hi();
	bool hihi();
	bool bta();

	void enable(bool enable);

	float value();
	float average();
	float minimum();
	float maximum();

	float voltage();
	float rangeLow();
	float rangeHigh();

	void loop(General &general);
private:
	int _pin;

	int _raw;
	int _rawLow;
	int _rawHigh;

	float _value;
	float _rangeLow;
	float _rangeHigh;

	float _lolo;
	float _lo;
	float _hi;
	float _hihi;

	float _avg;
	float _min;
	float _max;

	bool _enable;
	bool _enableLolo;
	bool _enableLo;
	bool _enableHi;
	bool _enableHihi;
	bool _enableBTA;

	bool _isLolo;
	bool _isLo;
	bool _isHi;
	bool _isHihi;
	bool _isBTA;

	bool _firstCycle;
};

#endif