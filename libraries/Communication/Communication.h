/*
General Communication functionality

Serial communication including:
- dynamic payload size

Byte layout

unsigned int header
- always 0xAAAA --> 1010 1010 1010 1010 

unsigned word payloadSize
- 0 - 255
unsigned word type
- 0 - 255
int id
- 0 - 65535
	
byte[] payload

unsigned int footer
- always 0x5555 --> 0101 0101 0101 0101

*/

#define COMM_DEBUG

#ifndef Communication_h
#define Communication_h

#include <Communication.h>

class Communication {
public:
	Communication();

	void send();
	void read();

	char * readData(int type, int nr);
		
	void sendData(unsigned int payloadSize, unsigned int type, int id, const char * payload);
private:
	char _desc[6];
	char _payload[64];
};



#endif