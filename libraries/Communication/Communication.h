/*
General Communication functionality

Serial communication including:
- dynamic payload size

Byte layout

int header
- always 1234
unsigned int identifier
- 65535
  ||		-> payload size 2 - 64 (always even)
   ||		-> type 1 - 15
     ||		-> object id 0 - 99 (max 35 if type == 15)
  - example: payload: 32, type 12, object id = 88 -> 33288
byte[] payload
int footer
- always 4321

*/
#ifndef Communication_h
#define Communication_h

#include <Communication.h>

struct dataStruct {
	char data[16];
	dataStruct() {
		for (int i = 0; i < 16; i++)
			data[i] = 0;
	}
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
		
	void sendData(int payloadSize, int type, int nr, const char * payload);
private:
	char _desc[6];
	char _payload[64];
};



#endif