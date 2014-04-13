#include <DI.h>
#include <DO.h>
#include <AI.h>
#include <AO.h>

#include <IO.h>

#include <General.h>

#define SENSOR 0
#define PROBE 0
#define LED 1

General general;
DI DIs[] = {};
DO DOs[] = {};
AI AIs[] = {};
AO AOs[] = {};
IO _IO = IO();

void setup() {
    Serial.begin(9600);
    
    _IO.setRegisterOut(2,3,4,1);
}

int n = 0;
int l = 0;

void loop() {
    general.time();
    
    
    //(voltage - 0.5) * 100.0
    float pot = ((((float)analogRead(0)) * (5.0 / 1023.0)) - 0.5) * 100.0;
    
    Serial.println(pot);
    
    _IO.writeBit(100,pot > 10.0);
    _IO.writeBit(101,pot > 12.0);
    _IO.writeBit(102,pot > 14.0);
    _IO.writeBit(103,pot > 16.0);
    _IO.writeBit(104,pot > 18.0);
    _IO.writeBit(105,pot > 20.0);
    _IO.writeBit(106,pot > 22.0);
    _IO.writeBit(107,pot > 24.0);
    
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
    if(sizeof(DOs) > 0) {
        maxObjects = sizeof(DOs) / sizeof(DOs[0]);
        for(int i = 0; i < maxObjects; i++) {
            DOs[i].loop(general);
        }
    }
    if(sizeof(AIs) > 0) {
        maxObjects = sizeof(AIs) / sizeof(AIs[0]);
        for(int i = 0; i < maxObjects; i++) {
            AIs[i].loop(general);
        }
    }
    if(sizeof(AOs) > 0) {
        maxObjects = sizeof(AOs) / sizeof(AOs[0]);
        for(int i = 0; i < maxObjects; i++) {
            AOs[i].loop(general);
        }
    }
    
    _IO.write();
}
