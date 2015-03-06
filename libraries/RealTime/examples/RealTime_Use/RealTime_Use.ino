/*===============================================================
 *  Module   : RealTime_Use.cpp
 *  Autho    : Julio Cesar Torres (juliozohar@gmail.com)
 *  Type     : C/Arduino Source Code
 *  Date     : 2015/01/10
 *  Objective: Example of usage - RealTime library.
 *===============================================================
 *  (C) 2014 Licensed under CERN OHL v.1.2
 *===============================================================
 */

#include <RealTime.h>
#include <DS1307.h>
#include <Wire.h>

//Declare the RealTime object
RealTime RealTime;

//Method setup
void setup() {
  Serial.begin(9600);
  Serial.flush();
  Wire.begin();

  //Sets RTC date/time on three steps:
  // 1. stops the running clock;
  // 2. sets the new date/time value;
  // 3. restart the clock.
  RealTime.stop();
  RealTime.setDateTime(2015,1,21,0,20,0,5);
  RealTime.start();
}

//Method loop
void loop() {
  //Requests a date/time from RTC
  String tmestm = RealTime.getDateTime();
  Serial.println(tmestm);
  delay(1000);
}
