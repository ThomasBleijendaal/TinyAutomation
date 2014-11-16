#include <Time.h>
#include <Communication.h>
#include <IODriver.h>
#include <IO.h>
#include <ATmega328.h>
#include <DHT.h>

#include <Typical.h>
#include <AI.h>
#include <DI.h>
#include <DO.h>
#include <AO.h>
//#include <M.h>

#include <Device.h>
#include <PID.h>

#include <General.h>

#include <DHT.h>
#include <Wire.h>
//#include <SFE_BMP180.h>


/* **************************************** */
// Typicals, IODrivers //
General general = General(2, 1, 2);

int freeRam() {
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

// UNTYPICALS //
/* **************************************** */
//DHT QT_insideHumiditySensor(8, DHT22);
//DHT QT_outsideHumiditySensor(7, DHT22);
//SFE_BMP180 PT_barometricPressureSensor;

// TYPICALS //
AI *heatingPadTemperature = general.add(new AI(A3)); //, -10.0, 125.0, 10.0, 25.0, 35.0, 50.0, true, 41, 614, true));
//AI *QT_light = general.add(new AI(20)); //, 0.0, 100.0));
//AI *QT_light2 = general.add(new AI(21)); //, 0.0, 100.0));
/*AI *QT_insideHumidity = general.add(new AI(-1)); //, 0.0, 100.0, 10.0, 20.0, 60.0, 80.0));
AI *QT_outsideHumidity = general.add(new AI(-1)); //, 0.0, 100.0, 10.0, 20.0, 80.0, 100.0));
AI *TT_inside = general.add(new AI(-1)); //, 0.0, 40.0, 18.0, 20.0, 23.0, 25.0));
AI *TT_outside = general.add(new AI(-1)); //, 0.0, 40.0, 15.0, 18.0, 25.0, 30.0));
AI *PT_atmosphere = general.add(new AI(-1)); //, 980.0, 1050.0, 980.0, 990.0, 1020.0, 1030.0));
AI *TT_atmosphere = general.add(new AI(-1)); //, 0.0, 40.0, 15.0, 18.0, 25.0, 30.0));
AI *TT_heatingPad = general.add(new AI(22)); //, -10.0, 125.0, 10.0, 25.0, 35.0, 50.0, true, 41, 614, true));

DI *LS_open = general.add(new DI(2, true));
DI *LS_closed = general.add(new DI(4, true));

DO *M_evacuator = general.add(new DO(30));
DO *M_agitator = general.add(new DO(31));
*/
//M *M_hatch = general.add(new M());

AO *heatingPad = general.add(new AO(3));

PID *heatingPadController = general.add(new PID(&heatingPadTemperature, &heatingPad));

void setup() {
	Serial.begin(115200);

	general.io.registerDriver(0,20,new ATmega328(), IOinstant);
	//general.io.registerDriver(30,31,new DHT(), IOinterrupt);

	//general.io.digitalWrite(32,true);
	//general.io.digitalWrite(33, true);

	//general.io.setRegisterOut(2, 7, 4, 1);

	//M_hatch->doubleCoil(34, 36, 35, 37);

	//PT_barometricPressureSensor.begin();

	//  TC_heatingPad->sp(24.0);
	//  TC_heatingPad->activate(true);

	heatingPadTemperature->settings.rangeLow = -10.0;
	heatingPadTemperature->settings.rangeHigh = 125.0;
	heatingPadTemperature->settings.rawLow = 41;
	heatingPadTemperature->settings.rawHigh = 614;

	heatingPadController->settings.P = 1.00;
	heatingPadController->settings.I = 0U;
	heatingPadController->settings.D = 3000U;
	heatingPadController->data.sp = 42.0;

	general.begin();
}

void loop() {
	heatingPadController->status.active = heatingPadTemperature->data.value < 50.0;
	general.loop();
}