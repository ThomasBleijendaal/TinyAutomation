/*
General Typical functionality

Includes
- OS: one shots: timed bools
- B: blink: blinking bools
- Serial communication (very beta)
*/
#ifndef General_h
#define General_h

#include <General.h>

struct dataStruct {
	char data[16];
};

struct commStruct {
	int header;
	int type;
	int nr;
	dataStruct data;
	int footer;

	commStruct() {
		header = 1234;
		type = 0;
		nr = 0;
		footer = 4321;
	}
};

const int typeDI = 1;
const int typeAI = 2;
const int typeM = 3;

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

		unsigned long cps;

		void time();

		void send();
		void read();

		dataStruct readData(int type, int nr);
		void stageSend(int type, int nr, dataStruct data);
    
	private:
		unsigned long _t2_5ms;
        int _t100ms;
        int _t250ms;
        int _t1s;
        int _t5s;
		int _t1m;
		int _t5m;
		
		int _sendBufferI;
		int _readBufferI;

		bool _send;

		//commStruct _sendBuffer[];
		//commStruct _readBuffer[1];

		unsigned long _cps;
};



#endif