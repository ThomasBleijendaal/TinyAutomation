/*
General Communication functionality
*/

#ifndef Communication_h
#define Communication_h

struct CommunicationHeader
{
	unsigned char header : 8;
	unsigned char sourceAddress : 8;
	unsigned char destinationAddress : 8;
	unsigned int payloadSize : 16;
	unsigned int comId : 16;
	int id : 16;

	CommunicationHeader(unsigned char sourceAddress, unsigned char destinationAddress, unsigned int payloadSize, unsigned char comId, int id)
		: header(0xAA),
		sourceAddress(sourceAddress),
		destinationAddress(destinationAddress),
		payloadSize(payloadSize),
		comId(comId),
		id(id) {};
};

struct CommunicationFooter
{
	unsigned char footer : 8;

	CommunicationFooter() : footer(0x55) {};
};

struct RemoteCommunication
{
	unsigned char header : 8;
	int communicationId : 16;
	unsigned char sourceAddress : 8;
	unsigned int comId : 16;
	int id : 16;
	unsigned char footer : 8;

	RemoteCommunication(int communicationId, unsigned char sourceAddress, unsigned int comId, int id) 
		: header(0xBB),
		communicationId(communicationId), 
		sourceAddress(sourceAddress),
		comId(comId),
		id(id),
		footer(0x55) {};
};

class Communication {
public:
	Communication();

	void setLocalAddress(unsigned char localAddress) { _localAddress = localAddress; };
	void setNodeAddress(unsigned char nodeAddress) { _nodeAddress = nodeAddress; };

	void loop();
	void begin();
	void setup();

	void sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload);
	void sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload, unsigned char nodeAddress);

	static int remoteAddress(unsigned char remoteAddress, unsigned int comId, int id);
private:
	bool started;

	unsigned char _localAddress;
	unsigned char _nodeAddress;

	static int _RemoteSubscriberId;
};

#endif