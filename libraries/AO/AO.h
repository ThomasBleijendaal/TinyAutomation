/*
Analog Input

Writes an analog output (PWM). Recieves a 0 - 100 % input which is converted to 0 - 255. Minimum and maximum output are in %. Rate of change is % / s.

*/
#ifndef AO_h
#define AO_h

#define AO_COM_settings_ID 0x03
#define AO_COM_status_ID 0x04
#define AO_COM_data_ID 0x05

#include <Typical.h>
#include <Time.h>
#include <Communication.h>
#include <IO.h>

struct AO_settings_t {
	float minOutput;
	float maxOutput;
	float rateOfChange;

	AO_settings_t() : minOutput(0.0), maxOutput(100.0), rateOfChange(-1.0) {};
};
struct AO_status_t {
	bool interlock : 1;
	bool active : 1;
	bool wasActive : 1;

	AO_status_t() : interlock(false), active(false), wasActive(false) {};

};
struct AO_data_t {
	float avg;

	float activeTime;
	unsigned int startCount;

	float output;
	float currentOutput;

	AO_data_t()
		: avg(0.0),
		activeTime(0.0),
		startCount(0),
		output(0.0),
		currentOutput(0.0) {}
};

// char, char, int, float, float =2h2f
struct AO_commSend_t {
	AO_status_t status;
	AO_data_t data;
};

class AO : public Typical {
public:
	AO();
	AO(int address) : _address(address) {};

	void begin(Time * time, Communication * communication, IO * io);
	void loop(Time * time, Communication * communication, IO * io);

	AO_settings_t settings;
	AO_status_t status;
	AO_data_t data;
private:
	int _address;
};

#endif