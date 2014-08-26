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
DI DIs[] = {
    DI(LS_open,12,true),DI(LS_closed,13,true)
};

/* **************************************** */
#define M_evacuator 0
#define M_agitator 1
DO DOs[] = {
    DO(M_evacuator,100),
    DO(M_agitator,101)
};

/* **************************************** */
#define M_hatch 0
M Ms[] = {
    M(M_hatch)
};

/* **************************************** */
//float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh
#define QT_insideHumidity 0
#define QT_outsideHumidity 1
#define TT_inside 2
#define TT_outside 3
#define PT_atmosphere 4
#define TT_atmosphere 5
#define QT_light 6
#define QT_light2 7
#define TT_heatingPad 8
AI AIs[] = {
    AI(QT_insideHumidity, -1, 0.0, 100.0, 10.0, 20.0, 60.0, 80.0),
    AI(QT_outsideHumidity, -1, 0.0, 100.0, 10.0, 20.0, 80.0, 100.0),
    AI(TT_inside, -1, 0.0, 40.0, 18.0, 20.0, 23.0, 25.0),
    AI(TT_outside, -1, 0.0, 40.0, 15.0, 18.0, 25.0, 30.0),
    AI(PT_atmosphere, -1, 980.0, 1050.0, 980.0, 990.0, 1020.0, 1030.0),
    AI(TT_atmosphere, -1, 0.0, 40.0, 15.0, 18.0, 25.0, 30.0),
    AI(QT_light, 0, 0.0, 100.0),
    AI(QT_light2, 1, 0.0, 100.0),
    //AI(TT_heatingPad, 2, -40.0, 125.0, 10.0, 25.0, 35.0, 50.0, true, 20, 360)
    AI(TT_heatingPad, 2, -10.0, 125.0, 10.0, 25.0, 35.0, 50.0, true, 41, 614, true)
};

/* **************************************** */
// int pin, float min, float max, float rate //
#define X_heatingPad 0
AO AOs[] = {
    AO(X_heatingPad,3,0.0,100.0)
};

/* **************************************** */
// int AI, float min, float max, int AO, float P, float I, float D
#define TC_heatingPad 0u
PID PIDs[] = {
    PID(TC_heatingPad, TT_heatingPad, 0.0, 100.0, X_heatingPad, 3.0, 0.2, 1.0)
};

void setup() {
    Serial.begin(115200);
    
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
    
    
    PIDs[TC_heatingPad].sp(32.0);
    PIDs[TC_heatingPad].activate(true);
    
    //general.send();   
    io.write();
}

/* **************************************** */

bool vent = false;
void program() {
    //vent = AIs[QT_light].value() > 70.0;
    
    //AOs[X_LED].output(AIs[QT_light].value());
    //AOs[X_LED].activate(AIs[QT_light].value() > 40.0);
    
    //ventilate(vent);
    
    //DOs[M_agitator].activate(vent);
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
        if (status != 0 && T == T) {
            AIs[TT_atmosphere].setValue(T);
            status = PT_barometricPressureSensor.startPressure(3);
            if (status != 0) {
                delay(status);

                status = PT_barometricPressureSensor.getPressure(P,T);
                if (status != 0 && P == P) {
                    AIs[PT_atmosphere].setValue(P);
                }
            }
        }
    }
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

