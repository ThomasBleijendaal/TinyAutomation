#include <Time.h>
#include <Communication.h>
#include <IODriver.h>
#include <IO.h>
#include <ATmega32u4.h>
#include <HC595.h>

#include <Typical.h>
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

AI test = AI(0,0.0,100.0);

void setup() {
  Serial.begin(115200);
  Serial.println(" jeej ");

  Serial.println(sizeof(test));
}

void loop() {
  
  
}

/* **************************************** */
