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

#include <General.h>

/* **************************************** */
General general = General(3, 1, 1);

// TYPICALS //
DO *led;
DI *button;

void setup() {
	Serial.begin(115200);

	// TODO: this should be automatic
	general.communication.setAddress(100);
	general.communication.setRemoteAddress(1);

	general.io.registerDriver(0, 20, new ATmega328(), IOinstant);

	led = general.add(new DO(13));
	button = general.add(new DI(Communication::remoteAddress(101, 0), true));

	general.begin();
}

void loop() {
	general.loop();

	led->status.active = button->status.active;
}