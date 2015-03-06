/*===============================================================
* Aleph Flight Data Recorder v.001a
* Module  : AlephFDR.ino
* Type    : C/Arduino Source Code
* Author  : Julio Cesar Torres
* Date    : December 23rd 2014
* Remarks : Read and register timestamp (DS1307) and internal
*           temperature (LM35).
*================================================================
* (C) 2014 Licensed under CERN OHL v.1.2
*================================================================
*       Pinout
* ==============================
*  LM35       - A0
*  DS1307 SCL - A4 || I2C DATA
*  DS1307 SCK - A5 || I2C CLOCK
* ==============================
*/
#include "AlephFDR.h"
#include <RealTime.h>
#include <DS1307.h>
#include <Wire.h>

boolean readyToWrite = false;
int cont_reg;
int pinTempInt = IO_PIN_TEMP_INT;

float valSensor  = 0;  //Stores the voltage read by sensor
float temp_raw   = 0;  //Stores the raw temperature
float temp       = 0;  //Stores the calibrated temperature

String inputString = "";
String raw001a = "";

RealTime RealTime;

/*
  Setup method.
*/
void setup() {
  Serial.begin(9600);
  Serial.flush();
  Wire.begin();
  analogReference(INTERNAL);
  cont_reg = 0;
}

/*
  Main loop method.
*/
void loop() {
	//Look for commands issued by user
	while (Serial.available() > 0){
	        char thisChar = Serial.read();
		inputString += thisChar;
		if (thisChar == '\n' ||
        thisChar == '\r' ||
        thisChar == '\0'){
			readyToWrite = true;
		}
	}
	if(readyToWrite){
		lookForTag();
	}

    do_sensing();
    write_record();
    delay(DELAY_TIME);
}

/*
  Does all the sensing work, and moves the values to the variables.
*/
void do_sensing(){
    cont_reg++;
    get_temp_int();
}

/*
  Reads the temperature from the analog sensor.
*/
void get_temp_int(){
  temp_raw = 0;
  valSensor = analogRead(pinTempInt);
  celsius(valSensor);
}

/*
  Converts reading into celsius degrees.
*/
void celsius(int valSensor){
  temp_raw = valSensor * FAT_MULT_ANLG;
  temp_raw = (temp_raw + CAL_OFFSET_LM35);
}

/*
  Writes the record to the configured output.
*/
void write_record(){
		char tmp_cont[6];    //TODO: optimize this
    char tmp_raw[6];     //TODO: optimize this
    String ts =  RealTime.getDateTime();
		raw001a += REG_TYPE;
		raw001a += REG_NAME;
		raw001a += sprintf(tmp_cont,"%5d", cont_reg);
		raw001a += ts;

		if(temp_raw >=0){
			raw001a += "+";
		}else{
			raw001a += "-";
		}
    raw001a += dtostrf(temp_raw, 4,2,tmp_raw);
    Serial.println(raw001a);
    cleanup();
}

void cleanup(){
  raw001a = "";
}

/*
  Looks for command issued by user. If none is found, issue a message.
*/
void lookForTag(){

  Serial.println(inputString);
	if(inputString.startsWith("date")){
		setDate();
	}else if (inputString.startsWith("version")){
		version();
	}else if (inputString.startsWith("showdate")){
		showdate();
	}else if (inputString.startsWith("help")){
    help();
  }else{
	 Serial.println("Invalid command.");
	}
  inputString = "";
  readyToWrite = false;
}

/* ===================
      User Commands
   =================== */
/*
  Sets the RTC's date/time variables.
  Input format: date yyyy-mm-dd-hh.mm.ss
*/
void setDate(){
	RealTime.stop();
	RealTime.setDateTime(
	inputString.substring(5,9).toInt(),
	inputString.substring(10,12).toInt(),
	inputString.substring(13,15).toInt(),
	inputString.substring(16,18).toInt(),
	inputString.substring(19,21).toInt(),
	inputString.substring(22,24).toInt(),
	1); //TODO: set day of week correctly
	RealTime.start();
}

/*
  Displays the date currently set on the RTC.
  Format: showdate
*/
void showdate(){
	Serial.println(RealTime.getDateTime());
}

/*
  Displays the firware current version.
  Format: version
*/
void version(){
	Serial.print("Aleph Flight Data Recorder, version ");
	Serial.println(VERSION);
}

/*
  Displays the list of commands available.
  Format: help
*/
void help(){
	Serial.println("");
	Serial.println("List of available commands:");
	Serial.println("date - sets RTC date/time;");
	Serial.println("showdate - displays the date currently set on the RTC;");
	Serial.println("version - displays the current firmware version;");
	Serial.println("help - displays this list of available commands.");
	Serial.println("For a comprehensive description of each command, please refer to the user's manual");
}
