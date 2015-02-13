#include <Time.h>
#include <Communication.h>
#include <IODriver.h>
#include <IO.h>
#include <ATmega32u4.h>

#include <Typical.h>
#include <AI.h>
#include <DI.h>
#include <DO.h>
#include <AO.h>
//#include <M.h>

#include <Device.h>
#include <PID.h>

#include <Application.h>
#include <General.h>

/* **************************************** */

// todo removal
General general = General(2, 0, 1);

void setup()
{
	general.setup();
}

void loop()
{
	general.loop();
}

// TYPICALS //
DI *button;
DO *led;

class Program : public Application {
public:
	DI *test;

	void setup() {
		general.communication.setLocalAddress(0xA1);
		general.communication.setNodeAddress(0x01);

		general.io.registerDriver(0, 20, new ATmega32u4(), IOinstant);

		button = general.add(new DI(Communication::remoteAddress(0xA0, DI_COM_data_ID, 0), true));
		led = general.add(new DO(10));
		test = general.add(new DI(1));
	}

	void onStart() {

	}

	bool onSerialError() {
		return false;
	}

	void loop() {

		led->status.active = button->status.active;

	}
};
Program program = Program();