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

        bool t100ms;
        bool t250ms;
        bool t1s;
        bool t5s;

		bool b1s;
        
		int cyclicLoad;

		void time();
    
	private:
        unsigned int _t100ms;
        unsigned int _t250ms;
        unsigned int _t1s;
        unsigned int _t5s;
		unsigned int _cps;
};



#endif