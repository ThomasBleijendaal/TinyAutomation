/*
PID controller

Basic implementation of a very naive PID controller.

*/
#ifndef PID_h
#define PID_h

#define PID_COM_settings_ID 0xA0
#define PID_COM_status_ID 0xA1
#define PID_COM_data_ID 0xA2

#include <Device.h>
#include <Time.h>
#include <Communication.h>
#include <AI.h>
#include <AO.h>

struct PID_settings_t {
	float P;
	unsigned long I;
	float D;

	float minOutput;
	float maxOutput;

	float deviationLimit;

	PID_settings_t() : P(0.0), I(0.0), D(0.0), minOutput(0.0), maxOutput(100.0), deviationLimit(0.0) {};
};

struct PID_status_t {
	bool deviated : 1;
	bool wasDeviated : 1;
	bool active : 1;
	bool wasActive : 1;

	PID_status_t() : deviated(false), wasDeviated(false), active(false), wasActive(false) {};
};

struct PID_data_t {
	float previousError;
	float sp;

	int deviationDelay;

	PID_data_t() : previousError(0.0), sp(0.0), deviationDelay(0) {};

};

struct PID_history_t {
	float entry[10];

	PID_history_t() {
		for (int i = 0; i < 10; ++i)
			entry[i] = 0.0;
	};

	void add(float value) {
		for(int i = 9; i > 0; --i)
			entry[i] = entry[i - 1];
		entry[0] = value;
	};
	float total() {
		float result = 0.0;
		for(int i = 0; i < 10; ++i)
			result += entry[i];
		return result;
	};
	float delta() {
		return entry[0] - entry[9];
	};
};

struct PID_commSend_t {
	PID_status_t status;
	PID_data_t data;
};

class PID : public Device {
public:
	PID();
	PID(AI **input, AO **output) : _AI(*input), _AO(*output) {};

	void begin(Time * time, Communication * communication);
	void loop(Time * time, Communication * communication);

	PID_settings_t settings;
	PID_status_t status;
	PID_data_t data;

	PID_history_t history;
	PID_history_t historyDelta;
private:
	int _id;
	bool iTimer;
	bool dTimer;

	AI *_AI;
	AO *_AO;
};

#endif