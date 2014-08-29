/*
General Communication functionality

Includes
- Serial communication (beta)
*/
#ifndef Communication_h
#define Communication_h

#include <Communication.h>

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
const int typeDO = 4;
const int typeAO = 5;
const int typePID = 6;

class Communication {
    public:
		Communication();

		void send();
		void read();

		dataStruct readData(int type, int nr);
		void stageSend(int type, int nr, dataStruct data);
    
	private:
		
		int _sendBufferI;
		int _readBufferI;

		bool _send;

		//commStruct _sendBuffer[];
		//commStruct _readBuffer[1];
};



#endif