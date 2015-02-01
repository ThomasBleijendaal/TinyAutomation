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

#include <General.h>

/* **************************************** */
General general = General(2, 0, 1);

// TYPICALS //
DI *button;
DO *led;

void setup() {
	general.setup();

	general.communication.setLocalAddress(0xA1);
	general.communication.setNodeAddress(0x01);

	general.io.registerDriver(0, 20, new ATmega32u4(), IOinstant);

	button = general.add(new DI(Communication::remoteAddress(0xA0, DI_COM_data_ID, 0), true));
	led = general.add(new DO(10));

	general.begin();
}

void loop() {
	general.loop();

	if (general.time.t1s)
		led->status.active = !led->status.active;
	
	//led->status.active = button->status.active;
	
}