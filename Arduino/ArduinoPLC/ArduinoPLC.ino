#include <DI.h>
#include <DO.h>
#include <AI.h>
#include <AO.h>
#include <M.h>
#include <PID.h>
#include <DHT.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include <General.h>
#include <IO.h>

/* **************************************** */
General general;
IO io;

// UNTYPICALS //
/* **************************************** */
DHT QT_insideHumiditySensor(9,DHT22);
DHT QT_outsideHumiditySensor(8,DHT22);
SFE_BMP180 PT_barometricPressureSensor;

// TYPICALS //
/* **************************************** */
#define LS_open 0
#define LS_closed 1
#define button 2
DI DIs[] = {
    DI(12,true),DI(13,true),DI(11,true)
};

/* **************************************** */
#define M_evacuator 0
#define M_agitator 1
DO DOs[] = {
    DO(100),
    DO(101)
};

/* **************************************** */
#define M_hatch 0
M Ms[] = {
    M()
};

/* **************************************** */
//float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh
#define QT_insideHumidity 0
#define QT_outsideHumidity 1
#define TT_inside 2
#define TT_outside 3
#define PT_atmosphere 4
#define TT_atmosphere 5
AI AIs[] = {
    AI(-1, 0.0, 100.0, 10.0, 20.0, 60.0, 80.0, false, 0, 1023),
    AI(-1, 0.0, 100.0, 10.0, 20.0, 80.0, 100.0),
    AI(-1, 0.0, 40.0, 18.0, 20.0, 23.0, 25.0),
    AI(-1, 0.0, 40.0, 15.0, 18.0, 25.0, 30.0),
    AI(-1, 980.0, 1050.0, 980.0, 990.0, 1020.0, 1030.0),
    AI(-1, 0.0, 40.0, 15.0, 18.0, 25.0, 30.0)
};

/* **************************************** */
// int pin, float min, float max, float rate //
AO AOs[] = {
};

/* **************************************** */
PID PIDs[] = {
};

void setup() {
    Serial.begin(9600);
    
    io.setRegisterOut(2,7,4,1);
    
    Ms[M_hatch].doubleCoil(104,106,105,107);
    
    PT_barometricPressureSensor.begin();
}
 
void loop() {
    general.time();
    
    if(general.t5s) {
        interruptProgram();
    }
    
    program();
    interlocks();
    
    loopTypicals();
    
    io.write();
}

/* **************************************** */

bool vent = false;
void program() {
    vent = DIs[button].isActive();
    
    ventilate(vent);
    
    DOs[M_agitator].activate(vent);
}

void interruptProgram() {
    AIs[QT_insideHumidity].setValue(QT_insideHumiditySensor.readHumidity());
    AIs[TT_inside].setValue(QT_insideHumiditySensor.readTemperature());
    AIs[QT_outsideHumidity].setValue(QT_outsideHumiditySensor.readHumidity());
    AIs[TT_outside].setValue(QT_outsideHumiditySensor.readTemperature());
    
    char status;
    double T, P;
    
    status = PT_barometricPressureSensor.startTemperature();
    if (status != 0) {
        delay(status);
        status = PT_barometricPressureSensor.getTemperature(T);
        if (status != 0) {
            AIs[TT_atmosphere].setValue(T);
            status = PT_barometricPressureSensor.startPressure(3);
            if (status != 0) {
                delay(status);

                status = PT_barometricPressureSensor.getPressure(P,T);
                if (status != 0) {
                    AIs[PT_atmosphere].setValue(P);
                }
            }
        }
    }
    
    Serial.println(AIs[TT_atmosphere].value());
    Serial.println(AIs[TT_outside].value());
    Serial.println(AIs[PT_atmosphere].value());
    Serial.println(AIs[QT_outsideHumidity].value());
}

void interlocks() {
    Ms[M_hatch].interlock(DIs[LS_open].isActive(),false,false,DIs[LS_closed].isActive(),false,false);
    DOs[M_evacuator].interlock(!DIs[LS_open].isActive(),false,false);
}

void ventilate(bool ventilate) {
    bool endPosition = (ventilate && DIs[LS_open].isActive()) || (!ventilate && DIs[LS_closed].isActive());
    
    Ms[M_hatch].activate(!endPosition,!ventilate);
    DOs[M_evacuator].activate(endPosition && ventilate);
}

/* **************************************** */

void loopTypicals() {
    //_IO.read(general);
    
    int maxObjects = 0;
    
    // INPUTS //
    if(sizeof(DIs) > 0) {
        maxObjects = sizeof(DIs) / sizeof(DIs[0]);
        for(int i = 0; i < maxObjects; i++) {
            DIs[i].loop(general);
        }
    }
    if(sizeof(AIs) > 0) {
        maxObjects = sizeof(AIs) / sizeof(AIs[0]);
        for(int i = 0; i < maxObjects; i++) {
            AIs[i].loop(general);
        }
    }
    
    // CONTROLLERS //
    if(sizeof(PIDs) > 0) {
        maxObjects = sizeof(PIDs) / sizeof(PIDs[0]);
        for(int i = 0; i < maxObjects; i++) {
            PIDs[i].value(AIs[PIDs[i].AI()].value());
            PIDs[i].loop(general);
            AOs[PIDs[i].AO()].output(PIDs[i].output());
            AOs[PIDs[i].AO()].activate(PIDs[i].isActive());
        }
    }
    
    // OUTPUTS //
    if(sizeof(DOs) > 0) {
        maxObjects = sizeof(DOs) / sizeof(DOs[0]);
        for(int i = 0; i < maxObjects; i++) {
            DOs[i].loop(general,io);            
        }
    }
    if(sizeof(AOs) > 0) {
        maxObjects = sizeof(AOs) / sizeof(AOs[0]);
        for(int i = 0; i < maxObjects; i++) {
            AOs[i].loop(general);
            
        }
    }
    if(sizeof(Ms) > 0) {
        maxObjects = sizeof(Ms) / sizeof(Ms[0]);
        for(int i = 0; i < maxObjects; i++) {
            Ms[i].loop(general,io);
        }
    }
}

