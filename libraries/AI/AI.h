/*
Analog Input

Reads an analog input. Maps the raw input to the configured range and determines if the input is out of range (bta, broken transmitter),
too high (hihi), high (hi), low (lo) or too low (lolo). Also computes a rolling average per 100ms.

*/
#ifndef AI_h
#define AI_h

#define AI_COM_settings_ID 0x00
#define AI_COM_status_ID 0x01
#define AI_COM_data_ID 0x02

#include <Typical.h>
#include <Time.h>
#include <Communication.h>
#include <IO.h>

struct AI_settings_t {
	bool enable : 1;
	bool enableLolo : 1;
	bool enableLo : 1;
	bool enableHi : 1;
	bool enableHihi : 1;
	bool enableBTA : 1;
	bool useFormatted : 1;
	bool useExternalValue : 1;

	int rawLow;
	int rawHigh;

	float rangeLow;
	float rangeHigh;

	float lolo;
	float lo;
	float hi;
	float hihi;

	AI_settings_t()
		: enable(true),
		enableLolo(false),
		enableLo(false),
		enableHi(false),
		enableHihi(false),
		enableBTA(false),
		useFormatted(false),
		useExternalValue(false),
		rawLow(0),
		rawHigh(1023),
		rangeLow(0.0),
		rangeHigh(100.0),
		lolo(0.0),
		lo(0.0),
		hi(0.0),
		hihi(0.0) {}
};
struct AI_status_t {
	bool isLolo : 1;
	bool isLo : 1;
	bool isHi : 1;
	bool isHihi : 1;
	bool isBTA : 1;

	AI_status_t() {}
};
struct AI_data_t {
	float value;

	float avg;
	float minValue;
	float maxValue;

	AI_data_t() : value(0.0), avg(0.0), minValue(0.0), maxValue(0.0) {}
};

struct AI_commSend_t {
	AI_status_t status;
	AI_data_t data;
};

class AI : public Typical {
public:
	AI() : _firstCycle(false) {};
	AI(int address) : _address(address), _firstCycle(false) {};

	void begin(Time * time, Communication * communication, IO * io);
	void loop(Time * time, Communication * communication, IO * io);

	AI_settings_t settings;
	AI_status_t status;
	AI_data_t data;
private:
	int _address;

	bool _firstCycle;
};

#endif
