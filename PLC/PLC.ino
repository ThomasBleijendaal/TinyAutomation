#include <Time.h>
#include <Communication.h>
#include <IODriver.h>
#include <IO.h>
#include <HC595.h>

#include <AI.h>
#include <DI.h>
#include <DO.h>
#include <AO.h>
#include <M.h>
#include <PID.h>

#include <General.h>

#include <DHT.h>
#include <Wire.h>
#include <SFE_BMP180.h>

/* **************************************** */
// AI, DI, AO, DO, M, PID //
General general = General(9, 2, 1, 2, 1, 1);

// UNTYPICALS //
/* **************************************** */
DHT QT_insideHumiditySensor(9, DHT22);
DHT QT_outsideHumiditySensor(8, DHT22);
SFE_BMP180 PT_barometricPressureSensor;

// TYPICALS //
AI &QT_light = general.addAI(AI(0, 0.0, 100.0));
AI &QT_light2 = general.addAI(AI(1, 0.0, 100.0));
AI &QT_insideHumidity = general.addAI(AI(-1, 0.0, 100.0, 10.0, 20.0, 60.0, 80.0));
AI &QT_outsideHumidity = general.addAI(AI(-1, 0.0, 100.0, 10.0, 20.0, 80.0, 100.0));
AI &TT_inside = general.addAI(AI(-1, 0.0, 40.0, 18.0, 20.0, 23.0, 25.0));
AI &TT_outside = general.addAI(AI(-1, 0.0, 40.0, 15.0, 18.0, 25.0, 30.0));
AI &PT_atmosphere = general.addAI(AI(-1, 980.0, 1050.0, 980.0, 990.0, 1020.0, 1030.0));
AI &TT_atmosphere = general.addAI(AI(-1, 0.0, 40.0, 15.0, 18.0, 25.0, 30.0));
AI &TT_heatingPad = general.addAI(AI(2, -10.0, 125.0, 10.0, 25.0, 35.0, 50.0, true, 41, 614, true));

DI &LS_open = general.addDI(DI(12, true));
DI &LS_closed = general.addDI(DI(3, true));

DO &M_evacuator = general.addDO(DO(20));
DO &M_agitator = general.addDO(DO(21));

M &M_hatch = general.addM(M());

AO &X_heatingPad = general.addAO(AO(3,0.0,100.0));

PID &TC_heatingPad = general.addPID(PID(&TT_heatingPad, 0.0, 100.0, &X_heatingPad, 0.3, 0.002, 3.0));

void setup() {
  Serial.begin(115200);

  general.io.registerDriver(20,27,new HC595(2, 7, 4, 1));

  //general.io.setRegisterOut(2, 7, 4, 1);

  M_hatch.doubleCoil(24, 26, 25, 27);

  PT_barometricPressureSensor.begin();

  TC_heatingPad.sp(24.0);
  TC_heatingPad.activate(true);
  
  general.io.begin();
}

void loop() {
  if (general.time.t5s) {
    interruptProgram();
  }

  program();
  interlocks();

  general.loop();
}

/* **************************************** */

bool vent = false;
void program() {

  vent = TT_heatingPad.average() > 20.0;

  ventilate(vent);
  M_agitator.activate(vent);

}

void interruptProgram() {
  char status;
  double T, P;

  status = PT_barometricPressureSensor.startTemperature();
  if (status != 0) {
    delay(status);
    status = PT_barometricPressureSensor.getTemperature(T);
    if (status != 0 && T == T) {
      TT_atmosphere.setValue(T);
      status = PT_barometricPressureSensor.startPressure(3);
      if (status != 0) {
        delay(status);

        status = PT_barometricPressureSensor.getPressure(P, T);
        if (status != 0 && P == P) {
          PT_atmosphere.setValue(P);
        }
      }
    }
  }
  
  QT_insideHumidity.setValue(QT_insideHumiditySensor.readHumidity());
  TT_inside.setValue(QT_insideHumiditySensor.readTemperature());
  
  QT_outsideHumidity.setValue(QT_outsideHumiditySensor.readHumidity());
  TT_outside.setValue(QT_outsideHumiditySensor.readTemperature());
}

void interlocks() {
  M_hatch.interlock(LS_open.isActive(), false, false, LS_closed.isActive(), false, false);
  M_evacuator.interlock(!LS_open.isActive(), false, false);
}

void ventilate(bool ventilate) {
  bool endPosition = (ventilate && LS_open.isActive()) || (!ventilate && LS_closed.isActive());

  M_hatch.activate(!endPosition, !ventilate);
  M_evacuator.activate(endPosition && ventilate);
}


