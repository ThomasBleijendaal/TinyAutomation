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

struct AI_settings_t {
	bool enable;
	bool enableLolo;
	bool enableLo;
	bool enableHi;
	bool enableHihi;
	bool enableBTA;
	bool damping;
	bool useFormatted;
	
	int rawLow;
	int rawHigh;
	
	float rangeLow;
	float rangeHigh;
	
	float lolo;
	float lo;
	float hi;
	float hihi;
	
	AI_settings_t() {}
};
struct AI_status_t {
	bool isLolo;
	bool isLo;
	bool isHi;
	bool isHihi;
	bool isBTA;
	
	AI_status_t() {}
};
struct AI_data_t {
	float value;

	float avg;
	float min;
	float max;
	
	AI_data_t() {}
};

struct AIdataStruct {
	AI_status_t status;
	AI_data_t data;
};

class AI : public Typical {
public:
	AI();
	AI(int address);

	void begin(Time * time, Communication * communication, IO * io);
	void loop(Time * time, Communication * communication, IO * io);
	
	AI_settings_t settings;
	AI_data_t data;
	AI_status_t status;
private:
	int _address;
	
	bool _firstCycle;
};

#endif