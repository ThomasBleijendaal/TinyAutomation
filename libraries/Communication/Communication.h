/*
General Communication functionality
*/

#ifndef Communication_h
#define Communication_h

#define CorrectHeader 0xAA
#define RemoteHeader 0xBB
#define CorrectFooter 0x55

#define CommunicationSendHeaderSize 9
struct CommunicationSendHeader
{
	unsigned char header : 8;
	unsigned char sourceAddress : 8;
	unsigned char destinationAddress : 8;
	unsigned int payloadSize : 16;
	unsigned int comId : 16;
	int id : 16;

	CommunicationSendHeader(unsigned char sourceAddress, unsigned char destinationAddress, unsigned int payloadSize, unsigned char comId, int id)
		: header(0xAA),
		sourceAddress(sourceAddress),
		destinationAddress(destinationAddress),
		payloadSize(payloadSize),
		comId(comId),
		id(id) {};
};

#define CommunicationReceiveHeaderSize 9
struct CommunicationReceiveHeader
{
	unsigned char header : 8;
	int communicationId : 16;
	unsigned int payloadSize : 16;
	unsigned int comId : 16;
	int id : 16;
};

#define CommunicationFooterSize 1
struct CommunicationFooter
{
	unsigned char footer : 8;

	CommunicationFooter() : footer(0x55) {};
};

#define RemoteCommunicationSize 9
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

class General;

class Communication {
public:
	Communication();
	bool isOk();

	void setLocalAddress(unsigned char localAddress) { _localAddress = localAddress; };
	void setNodeAddress(unsigned char nodeAddress) { _nodeAddress = nodeAddress; };

	void loop(General * general);
	void begin();
	void setup();

	void sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload);
	void sendData(unsigned int payloadSize, unsigned int comId, int id, const char * payload, unsigned char nodeAddress);

	static int remoteAddress(unsigned char remoteAddress, unsigned int comId, int id);
private:
	bool started;

	unsigned char _localAddress;
	unsigned char _nodeAddress;

	int * _remoteSubscribers;

	static int _remoteSubscriberId;
};

#endif