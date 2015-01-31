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
General general = General(2, 0, 1);

// TYPICALS //
DI *button;
DO *led;

void setup() {
	Serial.begin(115200);

	while (!Serial);

	general.communication.setLocalAddress(0xA0);
	general.communication.setNodeAddress(0x01);

	general.io.registerDriver(0, 20, new ATmega328(), IOinstant);

	button = general.add(new DI(8, true));
	led = general.add(new DO(13));

	general.begin();
}

void loop() {
	general.loop();

	if (general.time.t1s)
		led->status.active = !led->status.active;
	
	//led->status.active = button->status.active;
}