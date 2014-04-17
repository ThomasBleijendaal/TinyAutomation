#include <DI.h>
#include <DO.h>
#include <AI.h>
#include <AO.h>

#include <IO.h>

#include <General.h>

#define SENSOR 0
#define PROBE 0
#define LED 0

General general;
IO io;

DI DIs[] = {};
DO DOs[] = {DO(100),DO(101),DO(102)};
AI AIs[] = {};
AO AOs[] = {};

void setup() {
    Serial.begin(9600);
    
    io.setRegisterOut(8,2,4,1);
    pinMode(7,OUTPUT);
}

int n = 0;
int l = 0;

void loop() {
    general.time();
    
    
    //(voltage - 0.5) * 100.0
    float pot = ((((float)analogRead(0)) * (5.0 / 1023.0)) - 0.5) * 100.0;
    
    /*general.io.writeBit(100,pot > 10.0);
    _IO.writeBit(101,pot > 12.0);
    _IO.writeBit(102,pot > 14.0);
    _IO.writeBit(103,pot > 16.0);
    _IO.writeBit(104,pot > 18.0);
    _IO.writeBit(105,pot > 20.0);
    _IO.writeBit(106,pot > 22.0);*/
    io.writeBit(107,true);
    
    loopTypicals();
}

void loopTypicals() {
    //_IO.read(general);
    
    int maxObjects = 0;
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
    
    io.write();
}
