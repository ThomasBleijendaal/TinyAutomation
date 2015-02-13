#include <Time.h>
#include <Communication.h>
#include <IODriver.h>
#include <IO.h>
#include <ATmega328.h>

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

class Program : public Application {
public:
	DI * button;
	DO * led;

	void setup() {
		general.communication.setLocalAddress(0xA0);
		general.communication.setNodeAddress(0x01);

		general.io.registerDriver(0, 20, new ATmega328(), IOinstant);

		button = general.add(new DI(8, true));
		led = general.add(new DO(13));
	}

	void onStart() {

	}

	bool onSerialError() {
		return true;
	}

	void loop() {

		led->status.active = button->status.active;

	}
};
Program program = Program();