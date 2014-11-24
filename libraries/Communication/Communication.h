/*
General Communication functionality

Serial communication including:
- dynamic payload size

Byte layout

unsigned int header
- always 0xAAxx --> 1010 1010 address remoteAddress 

unsigned char payloadSize
- 0 - 255
unsigned char comId
- 0 - 255
int id
- 0 - 65535
	
byte[] payload

unsigned int footer
- always 0x5555 --> 0101 0101 0101 0101

*/

#ifndef Communication_h
#define Communication_h

struct CommunicationHeader
{
	unsigned char header : 8;
	unsigned char address : 4;
	unsigned char remoteAddress : 4;
	unsigned char payloadSize : 8;
	unsigned char comId : 8;
	int id : 16;

	CommunicationHeader(unsigned char address, unsigned char remoteAddress, unsigned char payloadSize, unsigned char comId, int id)
		: header(0xAA),
		address(address),
		remoteAddress(remoteAddress),
		payloadSize(payloadSize),
		comId(comId),
		id(id) {};
};

struct CommunicationFooter
{
	unsigned int footer : 16;

	CommunicationFooter() : footer(0x5555) {};
};

class Communication {
public:
	Communication();

	void setAddress(unsigned char address) { _address = address; };
	void setRemoteAddress(unsigned char remoteAddress) { _remoteAddress = remoteAddress; };

	void send();
	void read();

	char * readData(int type, int nr);
		
	void sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload);
	void sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload, unsigned char remoteAddress);
private:
	char _desc[6];
	char _payload[64];

	unsigned char _address;
	unsigned char _remoteAddress;
};



#endif