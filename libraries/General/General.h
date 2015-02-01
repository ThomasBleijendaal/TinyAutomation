/*
General functionality

Main object of the PLC which provides a place to store Typicals, Devices and which deals with the external communication, time handling and IO drivers.

*/
#ifndef General_h
#define General_h

#include <Communication.h>
#include <Time.h>
#include <IO.h>

#include <AI.h>
#include <DI.h>
#include <AO.h>
#include <DO.h>

//#include <M.h>
#include <PID.h>


class General {
    public:
		General(int typicalCount, int deviceCount, int ioCount);

		template <class T>
		T * add(T * object);

		void loop();
		void begin();
		void setup();

		Communication communication;
		Time time;
		IO io;

	private:
		Typical ** _typicals;
		Device ** _devices;

		void _add(Typical * object);
		void _add(Device * object);

		int _typicalCount;
		int _deviceCount;
};

#endif