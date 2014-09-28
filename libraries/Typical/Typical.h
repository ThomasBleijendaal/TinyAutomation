/*
Typical class

Provides base for every typical

*/
#ifndef Typical_h
#define Typical_h

#include <Time.h>
#include <Communication.h>
#include <IO.h>

class Typical {
public:
	Typical();

	void setId(int id);

	virtual void begin(Time * time, Communication * communication, IO * io);
	virtual void loop(Time * time, Communication * communication, IO * io);
protected:
	int _id;
};

#endif