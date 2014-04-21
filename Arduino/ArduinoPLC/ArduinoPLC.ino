#include <DI.h>
#include <DO.h>
#include <AI.h>
#include <AO.h>
#include <PID.h>

#include <IO.h>

#include <TFT.h>
#include <SPI.h>

#include <General.h>

#define LED 0
#define POT 1
#define LUX 0
#define BUTTON 0
#define LUXcontrol 0

General general;

TFT tft = TFT(10,9,8);

IO io;

//  //
DI DIs[] = {DI(2,true)};

//  //
DO DOs[] = {};

// LUX,POT //
//float rangeLow, float rangeHigh, float lolo, float lo, float hi, float hihi, bool enableBTA, int rawLow, int rawHigh
AI AIs[] = {
    AI(0,0.0,100.0,5.0,15.0,85.0,95.0,false,100,600),
    AI(1,0.0,100.0,-1.0,-1.0,101.0,101.0,false,0,1023)
};
// LED //
// int pin, float min, float max, float rate //
AO AOs[] = {AO(3,0.0,100.0,-1)};

// LUXcontrol //
PID PIDs[] = {PID(20.0,100.0,LUX,LED)};

void setup() {
    Serial.begin(9600);
    
    tft.begin();
    tft.background(0, 0, 0);
    tft.stroke(255,255,255);
    tft.setTextSize(1);
}

void loop() {
    general.time();
//  start code //

    PIDs[LUXcontrol].sp(AIs[POT].value());
    PIDs[LUXcontrol].activate(true); //DIs[BUTTON].isActive());



//  end code //
    loopTypicals();
}

void loopTypicals() {
    //_IO.read(general);
    
    int line = 0;
    String s;
    char str[8];
    
    if(general.t1s)
        tft.background(0, 0, 0);
    
    int maxObjects = 0;
    
    // INPUTS //
    if(sizeof(DIs) > 0) {
        maxObjects = sizeof(DIs) / sizeof(DIs[0]);
        for(int i = 0; i < maxObjects; i++) {
            DIs[i].loop(general);
            
            if(general.t1s) {
                tft.text("DI",0,line * 8);
                
                if(DIs[i].isActive())
                    tft.text("active",20,line * 8);
                else
                    tft.text("inactive",20,line * 8);
                
                line++;
            }
        }
    }
    if(sizeof(AIs) > 0) {
        maxObjects = sizeof(AIs) / sizeof(AIs[0]);
        for(int i = 0; i < maxObjects; i++) {
            AIs[i].loop(general);
            
            if(general.t1s) {
                tft.text("AI",0,line * 8);
                
                s = String(AIs[i].value());
                s.toCharArray(str,8);
                
                tft.text(str,20,line * 8);                
                tft.text("EU =",70,line*8);
                
                s = String(AIs[i].voltage());
                s.toCharArray(str,8);
                
                tft.text(str,100,line * 8);                
                tft.text("V",130,line*8);
                
                line++;
            }
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
            
            if(general.t1s) {
                tft.text("PID",0,line * 8);
                
                s = String(PIDs[i].value());
                s.toCharArray(str,8);
                
                tft.text(str,20,line * 8);                
                tft.text("EU; ",70,line*8);
                
                s = String(PIDs[i].sp());
                s.toCharArray(str,8);
                
                tft.text(str,100,line * 8);                
                tft.text("EU",130,line*8);
                
                line++;
                tft.text(" ",0,line * 8);
                
                s = String(PIDs[i].output());
                s.toCharArray(str,8);
                
                tft.text(str,20,line * 8);                
                tft.text("%",70,line*8);
                
                line++;
            }
        }
    }
    
    // OUTPUTS //
    if(sizeof(DOs) > 0) {
        maxObjects = sizeof(DOs) / sizeof(DOs[0]);
        for(int i = 0; i < maxObjects; i++) {
            DOs[i].loop(general,io);
            
            if(general.t1s) {
                tft.text("DO",0,line * 8);
                
                if(DOs[i].isActive())
                    tft.text("active",20,line * 8);
                else
                    tft.text("inactive",20,line * 8);
                
                line++;
            }
        }
    }
    if(sizeof(AOs) > 0) {
        maxObjects = sizeof(AOs) / sizeof(AOs[0]);
        for(int i = 0; i < maxObjects; i++) {
            AOs[i].loop(general);
            
            if(general.t1s) {
                tft.text("AO",0,line * 8);
                
                s = String(AOs[i].output());
                s.toCharArray(str,8);
                
                tft.text(str,20,line * 8);
                tft.text("EU =",70,line*8);
                
                s = String(AOs[i].voltage());
                s.toCharArray(str,8);
                
                tft.text(str,100,line * 8);                
                tft.text("V",130,line*8);
                
                line++;
            }
        }
    }
    
    io.write();
}
