/*
Analog Input

Reads an analog input. Maps the raw input to the configured range and determines if the input is out of range (bta, broken transmitter), 
too high (hihi), high (hi), low (lo) or too low (lolo). Also computes a rolling average per 100ms.

*/
#ifndef AI_h
#define AI_h

#include <Typical.h>
#include <Time.h>
#include <Communication.h>
#include <IO.h>

// char, char, float, float, float, float =h4f
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
	float average;

	AIdataStruct() {
		value = 0.0;
		min = 0.0;
		max = 0.0;
		average = 0.0;
	}
};
/*struct AIcmdStruct {
	struct cmd {
		char spare : 8;
		cmd() {
			spare = 0;
		}
	};

};*/

class AI : public Typical {
public:
	AI();
	AI(int pin);
	AI(int pin, float rangeLow, float rangeHigh);
	AI(int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi);
	AI(int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh);
	AI(int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh, bool damping);

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

	void begin(Time * time, Communication * communication, IO * io);
	void loop(Time * time, Communication * communication, IO * io);
private:
	void _init(int pin, float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh, bool damping);

	int _pin : 2;

	int _raw : 2;
	int _rawLow : 2;
	int _rawHigh : 2;

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

	bool _enable : 1;
	bool _enableLolo : 1;
	bool _enableLo : 1;
	bool _enableHi : 1;
	bool _enableHihi : 1;
	bool _enableBTA : 1;
	bool _damping : 1;

	bool _isLolo : 1;
	bool _isLo : 1;
	bool _isHi : 1;
	bool _isHihi : 1;
	bool _isBTA : 1;

	bool _firstCycle : 1;
	bool _firstValueSet : 1;
};

#endif