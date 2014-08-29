/*
Motor Control

Controls a single or a double coil motor. Supports up to 3 interlocks per direction or rotation.
The clockwise or counter-clockwise operation of the motor is determined by the setupt of the pins.

TODO:
- Add support for other timings

*/
#ifndef M_h
#define M_h

#include <Time.h>
#include <Communication.h>
#include <IO.h>

struct MdataStruct {
	struct status {
		bool active : 1;
		bool reverse : 1;
		bool interlock : 1;
		bool interlockReverse : 1;
		char spare : 4;
		status() {
			active = false;
			reverse = false;
			interlock = false;
			interlockReverse = false;
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
	char spare[8];

	MdataStruct() {
		startCount = 0;
		activeTime = 0.0;
		spare[0] = 0;
		spare[1] = 0;
		spare[2] = 0;
		spare[3] = 0;
		spare[4] = 0;
		spare[5] = 0;
		spare[6] = 0;
		spare[7] = 0;
	}
};
class M {
public:
	M();
	
	void setId(int id);

	void singleCoil(int pin0, int pin1);
	void doubleCoil(int pin0, int pin1, int pin2, int pin3);

	bool isActive();
	unsigned int startCount();
	float activeTime();

	void activate(bool activate);
	void activate(bool activate, bool reverse);

	void interlock(bool i0, bool i1, bool i2, bool i3, bool i4, bool i5);
	void interlock(bool i0, bool i1, bool i2);

	void loop(Time &time, Communication &communication, IO &io);
private:
	int _id;
	int _pin[4];
	int _seq;
	int _maxPins;

	bool _active;
	bool _reverse;
	bool _wasActive;
	bool _interlock1;
	bool _interlock2;

	unsigned int _startCount;
	unsigned int _activeTime;
};

#endif