/*
General Typical functionality

Includes
- Communication class
- Time class
- IO class

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
#include <M.h>
#include <PID.h>


class General {
    public:
		General(int objectCount, int ioCount);

		template <class T>
		T * add(T * object);

		void loop();
		void begin();

		Communication communication;
		Time time;
		IO io;
    
	private:
		Typical ** _typicals;
		void _add(Typical * object);

		int _typicalCount;
};

#endif