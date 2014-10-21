/*
IO Driver for DHT 
Relative humidity and temperature

Adapted from Adafuit's library.

*/
#ifndef iodDHT_h
#define iodDHT_h

#include <IODriver.h>


class DHT : public IODriver {
public:
	DHT();

	void begin();
	void interrupt();

	float formattedRead(int address);


private:
	
};

#endif