/*
Digital Input

Reads a digital input. Counts the times the input is turned on and the duration of the input being on.

*/
#ifndef DI_h
#define DI_h

#define DI_COM_settings_ID 0x06
#define DI_COM_status_ID 0x07
#define DI_COM_data_ID 0x08

#include <Typical.h>
#include <Time.h>
#include <Communication.h>
#include <IO.h>

struct DI_settings_t {
	bool NC;

	DI_settings_t() : NC(false) {}
};
struct DI_status_t {
	bool active;
	bool activated;
	bool deActivated;

	DI_status_t() : active(false), activated(false), deActivated(false) {}
};
struct DI_data_t {
	unsigned int switchCount;
	float activeTime;

	DI_data_t() : switchCount(0), activeTime(0.0) {}
};

struct DI_commSend_t {
	DI_status_t status;
	DI_data_t data;
};

class DI : public Typical {
public:
	DI();
	DI(int address) : _address(address) {};
	DI(int address, bool NC) : _address(address) { settings.NC = NC; };

	void begin(Time * time, Communication * communication, IO * io);
	void loop(Time * time, Communication * communication, IO * io);

	void receiveData(unsigned int payloadSize, const char * data);

	DI_settings_t settings;
	DI_data_t data;
	DI_status_t status;
private:
	int _address;
};

#endif