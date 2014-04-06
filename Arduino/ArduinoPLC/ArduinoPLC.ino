#include <DI.h>
#include <DO.h>
#include <AI.h>

#include <General.h>

#define BUTTON 0
#define LEDlolo 0
#define LEDlo 1
#define LEDhi 2
#define LEDhihi 3
#define POT 0
#define TOUCH 1

General general;
DI DIs[] = {DI(2,false)};
DO DOs[] = {DO(3),DO(4),DO(5),DO(6)};
AI AIs[] = {AI(0,0.0,5.0,0.5,1.0,4.0,4.5,true),AI(1,0.0,5.0,0.5,1.0,4.0,4.5,true)};

bool enable = true;
int red = 0;
int gre = 64;
int blu = 128;

void setup() {
    Serial.begin(9600);
    
}

void loop() {
    general.time();
    loopTypicals();
    
    
    if(DIs[BUTTON].activated()) {
        enable = !enable;
    }
    
    DOs[LEDlolo].blink(enable && AIs[TOUCH].bta());
    DOs[LEDlo].blink(enable && AIs[TOUCH].bta());
    DOs[LEDhi].blink(enable && AIs[TOUCH].bta());
    DOs[LEDhihi].blink(enable && AIs[TOUCH].bta());
    
    DOs[LEDlolo].activate(enable && AIs[TOUCH].lolo() && !AIs[TOUCH].bta());
    DOs[LEDlo].activate(enable && AIs[TOUCH].lo() && !AIs[TOUCH].bta());
    DOs[LEDhi].activate(enable && AIs[TOUCH].hi() && !AIs[TOUCH].bta());
    DOs[LEDhihi].activate(enable && AIs[TOUCH].hihi() && !AIs[TOUCH].bta());
    
    Serial.println(AIs[TOUCH].value());
}

void loopTypicals() {
    int maxObjects = sizeof(DIs) / sizeof(DIs[0]);
    for(int i = 0; i < maxObjects; i++) {
        DIs[i].loop(general.t100ms,general.b1s);
    }
    maxObjects = sizeof(DOs) / sizeof(DOs[0]);
    for(int i = 0; i < maxObjects; i++) {
        DOs[i].loop(general.t100ms,general.b1s);
    }
    maxObjects = sizeof(AIs) / sizeof(AIs[0]);
    for(int i = 0; i < maxObjects; i++) {
        AIs[i].loop(general.t100ms,general.b1s);
    }
}
