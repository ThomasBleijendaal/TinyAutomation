/*
Analog Input

Reads an analog input. Maps the raw input to the configured range and determines if the input is out of range (bta, broken transmitter), 
too high (hihi), high (hi), low (lo) or too low (lolo). Also computes a rolling average per 100ms.


*/
#ifndef AI_h
#define AI_h

#include <AI.h>
#include <General.h>

struct AIdataStruct {
	struct status {
		bool lolo : 1;
		bool lo : 1;
		bool hi : 1;
		bool hihi : 1;
		bool bta : 1;
		char spare : 3;
		status() {
			lolo = false;
			lo = false;
			hi = false;
			hihi = false;
			bta = false;
			spare = 0;
		}
	} status;
	struct cmd {
		char spare : 8;
		cmd() {
			spare = 0;
		}
	} cmd;
	float value;
	float min;
	float max;
	char spare[2];

	AIdataStruct() {
		value = 0.0;
		min = 0.0;
		max = 0.0;
		spare[0] = 0;
		spare[1] = 0;
	}
};

class AI {
public:
	AI(int id, int pin);
	AI(int id, int pin, float rangeLow, float rangeHigh);
	AI(int id, int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi);
	AI(int id, int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh);
	AI(int id, int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh, bool damping);

	bool lolo();
	bool lo();
	bool hi();
	bool hihi();
	bool bta();

	void enable(bool enable);

	float value();
	void setValue(float value);
	float average();
	float minimum();
	float maximum();

	float voltage();
	float rangeLow();
	float rangeHigh();

	void loop(General &general);
private:
	void _init(int id, int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh, bool damping);

	int _id;
	int _pin;

	int _raw;
	int _rawLow;
	int _rawHigh;

	float _value;
	float _previousValue;
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
	bool _damping;

	bool _firstCycle;
	bool _firstValueSet;
};

#endif