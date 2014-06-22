#include <DI.h>
#include <DO.h>
#include <AI.h>
#include <AO.h>
#include <M.h>
#include <PID.h>
#include <General.h>
#include <IO.h>

/* **************************************** */
General general;
IO io;

#define button 0
DI DIs[] = {
    DI(11,true)
};

DO DOs[] = {};
AI AIs[] = {};
AO AOs[] = {};
PID PIDs[] = {};
M Ms[] = {};

void setup() {
    Serial.begin(115200);
    
}

void loop() {
    general.time();
    
    if(general.t5s) {
    //    interruptProgram();
    }
    
    program();
    interlocks();
    
    
    loopTypicals();
    
    
    general.send();
    io.write();
    
    /*
    if(Serial.available() > 0) {
        Serial.readBytes(recievedDataBytes, 18);
        
        memcpy(&recievedData, recievedDataBytes, 18);
        
        recievedData.data2 += 1.0;

        memcpy(&sendData, &recievedData, 18);
        
        memcpy(sendDataBytes, &sendData, 18);
        
        Serial.write(sendDataBytes,18);
                
        
    }*/
}

void program() {
    //Serial.println(DIs[button].isActive());
}
void interlocks() {
    
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
    
