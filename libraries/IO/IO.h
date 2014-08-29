/*
IO abstraction layer.

Currently supports
- Arduino UNO
- Output Shift Registers (have to be on 0-7)
- Digital output

*/
#ifndef IO_h
#define IO_h

class IO {
public:
	IO();

	void setRegisterOut(int dataPin, int clockPin, int latchPin, int writeBytes);
	void writeBit(int bit, bool value);
	void writeByte(int byte, unsigned char value);

	//void setRegisterIn(int dataPin, int clockPin, int loadPin, int readBytes);
	//bool readBit(int bit);
	//unsigned char readByte(int byte);

	//void read();
	void write();
private:
	int _dataWritePin;
	int _writeBytes;

	int _clockPin;
	int _latchPin;

	unsigned char _dataWritePinMask;
	unsigned char _clockPinMask;
	unsigned char _latchPinMask;

	bool _writeData[32];
};

#endif