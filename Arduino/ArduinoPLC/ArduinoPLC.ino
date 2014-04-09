#include <DI.h>
#include <DO.h>
#include <AI.h>
#include <AO.h>

#include <General.h>

#define SENSOR 0
#define PROBE 0
#define LED 1

General general;
DI DIs[] = {};
DO DOs[] = {DO(2),DO(3)};
AI AIs[] = {AI(0,0.0,100.0,5.0,10.0,90.0,95.0,true,0,1023)};
AO AOs[] = {};

bool test = false;

void setup() {
    Serial.begin(9600);
}

void loop() {
    general.time();
    
    if(test && general.t100ms) {
        test = false;
    }
    
    if(general.t1m) {
        test = true;
    }
    
    AIs[SENSOR].enable(test);
    DOs[PROBE].activate(test);
    DOs[LED].activate(test);
    
    if(DOs[PROBE].isActive()) {
        Serial.print(AIs[SENSOR].average());
        Serial.print("\t");
        Serial.println(AIs[SENSOR].value());
    }
    
    loopTypicals();
    
}

void loopTypicals() {
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
}
