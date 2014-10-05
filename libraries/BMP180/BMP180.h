/*
IO Driver for BMP180 
Barometric Pressure Sensor

Adapted from Sparkfun's library.

Address 0 yields pressure
Address 1 yields temperature


*/
#ifndef iodBMP180_h
#define iodBMP180_h

#include <IODriver.h>

#define BMP180_ADDR 0x77 // 7-bit address

#define	BMP180_REG_CONTROL 0xF4
#define	BMP180_REG_RESULT 0xF6

#define	BMP180_COMMAND_TEMPERATURE 0x2E
#define	BMP180_COMMAND_PRESSURE0 0x34
#define	BMP180_COMMAND_PRESSURE1 0x74
#define	BMP180_COMMAND_PRESSURE2 0xB4
#define	BMP180_COMMAND_PRESSURE3 0xF4

#define BMP180_DATA_TEMPERATURE 0
#define BMP180_DATA_PRESSURE 1

class BMP180 : public IODriver {
public:
	BMP180();

	void begin();
	void interrupt();

	float formattedRead(int address);

	char startTemperature(void);
	char getTemperature(float &T);
	char startPressure(char oversampling);
	char getPressure(float &P, float &T);

private:
	float data[2];

	char readInt(char address, int &value);
	char readUInt(char address, unsigned int &value);
	char readBytes(unsigned char *values, char length);
	char writeBytes(unsigned char *values, char length);

	int AC1, AC2, AC3, VB1, VB2, MB, MC, MD;
	unsigned int AC4, AC5, AC6;
	float c5, c6, mc, md, x0, x1, x2, y0, y1, y2, p0, p1, p2;
	char _error;
};

#endif