/*
Digital Output

Writes a digital output. Set the output according to its active state, counts the times the output is switched on and the time the output is on.

*/
#ifndef DO_h
#define DO_h

#define DO_COM_settings_ID 0x09
#define DO_COM_status_ID 0x0A
#define DO_COM_data_ID 0x0B

#include <Typical.h>
#include <Time.h>
#include <Communication.h>
#include <IO.h>

struct DO_settings_t {

};
struct DO_status_t {
	bool interlock;
	bool active;
	bool wasActive;

	DO_status_t() : interlock(false), active(false), wasActive(false) {};
};
struct DO_data_t {
	float activeTime;
	unsigned int startCount;

	DO_data_t() : activeTime(0.0), startCount(0) {}
};

struct DO_commSend_t {
	DO_status_t status;
	DO_data_t data;
};

class DO : public Typical {
public:
	DO();
	DO(int address) : _address(address) {};

	void begin(Time * time, Communication * communication, IO * io);
	void loop(Time * time, Communication * communication, IO * io);

	DO_settings_t settings;
	DO_status_t status;
	DO_data_t data;
private:
	int _address;
};

#endif