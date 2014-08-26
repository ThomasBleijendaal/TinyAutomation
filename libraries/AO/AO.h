/*
Analog Input

Writes an analog output (PWM). Recieves a 0 - 100 % input which is converted to 0 - 255. Minimum and maximum output are in %. Rate of change is % / s.

*/
#ifndef AO_h
#define AO_h

#include <AO.h>
#include <General.h>

struct AOdataStruct {
	struct status {
		bool active : 1;
		bool interlock : 1;
		char spare : 6;
		status() {
			active = false;
			interlock = false;
			spare = 0;
		}
	} status;
	struct cmd {
		char spare : 8;
		cmd() {
			spare = 0;
		}
	} cmd;
	int startCount;
	float activeTime;
	float output;
	char spare[4];

	AOdataStruct() {
		startCount = 0;
		activeTime = 0.0;
		output = 0.0;
		spare[0] = 0;
		spare[1] = 0;
		spare[2] = 0;
		spare[3] = 0;
	}
};

class AO {
public:
	AO(int id, int pin);
	AO(int id, int pin, float min, float max);
	AO(int id, int pin, float min, float max, float rate);

	void output(float output);
	void activate(bool activate);

	float output();
	float average();
	float activeTime();
	float voltage();

	void interlock(bool i0, bool i1, bool i2);

	void loop(General &general);

private:
	void _init(int id, int pin, float min, float max, float rate);

	int _id;
	int _pin;
	int _raw;

	bool _interlock;
	bool _active;
	bool _wasActive;

	float _output;
	float _currentOutput;

	float _avg;
	float _min;
	float _max;
	float _rate;

	unsigned int _activeTime;
	unsigned int _startCount;
};

#endif