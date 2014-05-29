/*
General Typical functionality

Includes
- OS: one shots: timed bools

*/
#ifndef General_h
#define General_h

#include <General.h>

class General {
    public:
        General();

		bool t2_5ms;
        bool t100ms;
        bool t250ms;
        bool t1s;
        bool t5s;
		bool t1m;
		bool t5m;

		bool b1s;

		int registerTimer(int millis);
		bool timer(int id);

		unsigned long cps;

		void time();
    
	private:
		unsigned long _t2_5ms;
        int _t100ms;
        int _t250ms;
        int _t1s;
        int _t5s;
		int _t1m;
		int _t5m;
		
		int _customTimer[3];
		int _customTimerCounter[3];
		bool _customTimerActive[3];

		unsigned long _cps;
};



#endif