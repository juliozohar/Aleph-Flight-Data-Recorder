#include <RealTime.h> 
#include <DS1307.h>
#include <Wire.h> 

RealTime RealTime; 

void setup() {
  Serial.begin(9600); 
  Serial.flush();
  Wire.begin();

  RealTime.stop(); 
  RealTime.setDateHour(2015,1,21,0,20,0,5);
  RealTime.start();   
}

void loop() {
  String tmestm = RealTime.getDateTime(); 
  Serial.println(tmestm);
  delay(1000); 
}
