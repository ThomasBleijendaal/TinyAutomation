/*
General Time functionality

Includes
- OS: one shots: timed bools
- B: blink: blinking bools
*/
#ifndef Time_h
#define Time_h

#include <Time.h>

class Time {
    public:
        Time();

		bool t2_5ms;
        bool t100ms;
        bool t250ms;
        bool t1s;
        bool t5s;
		bool t1m;
		bool t5m;

		bool b1s;

		unsigned long cps;

		void loop();
    
	private:
		unsigned long _t2_5ms;
        int _t100ms;
        int _t250ms;
        int _t1s;
        int _t5s;
		int _t1m;
		int _t5m;
		unsigned long _cps;
};

#endif