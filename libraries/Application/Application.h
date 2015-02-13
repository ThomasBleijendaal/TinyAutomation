/*

*/
#ifndef Application_h
#define Application_h

#include <General.h>

class General;

class Application {
public:
	Application();

	virtual void setup();
	virtual void onStart();
	virtual bool onSerialError();
	virtual void loop();
};

#endif