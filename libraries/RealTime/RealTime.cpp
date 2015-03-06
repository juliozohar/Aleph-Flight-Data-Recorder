/*===============================================================
 *  Module   : RealTime.cpp
 *  Autho    : Julio Cesar Torres (juliozohar@gmail.com)
 *  Type     : C++ Source
 *  Date     : 07/04/2014
 *  Objective: Library for using real time clock (RTC)facilities,
 *             based in a DS1307 IC implementation.
 *===============================================================
 *  (C) 2014 Licensed under CERN OHL v.1.2
 *===============================================================
 */
#include "RealTime.h"
#include "Wire.h"

#include "DS1307.h"

//Declare the time variables
int day, month, year;
int hour, minute, second;

 /*
  * Constructor.
  */
 RealTime::RealTime(){}

/*
 * Starts real time clock execution.
 */
void RealTime::start(){
  RTC.start();
}

/*
 * Stops real time clock execution.
 */
void RealTime::stop(){
  RTC.stop();
}

/*
 * Updates the date/time register in RTC. The RTC is keep effective while
 * there is current available to the circuit, either by the main power
 * supply lines, or by the backup battery connected directly to the circuit.
 * Receives the time variables separately, as the function signature denotes.
 */
void RealTime::setDateTime(int year, int month, int day,
        int hour, int minute, int second, int day_week){
  RTC.set(DS1307_SEC  , second );
  RTC.set(DS1307_MIN  , minute );
  RTC.set(DS1307_HR   , hour );
  RTC.set(DS1307_DOW  , day_week );
  RTC.set(DS1307_DATE , day );
  RTC.set(DS1307_MTH  , month);
  RTC.set(DS1307_YR   , year);
}

/*
 * Reads the latest timestamp in the real time clock.
 * TODO : The year register is always being returned as year 2000. I did't
 * find the problem's source, and to temporarily solve the issue, I add +15
 * to the year variable. Look for a solution in DS1307 documentation to fix
 * this bug.
 */
void RealTime::readRTC(){
  hour    = RTC.get(DS1307_HR,   true );
  minute  = RTC.get(DS1307_MIN,  false);
  second  = RTC.get(DS1307_SEC,  false);
  day     = RTC.get(DS1307_DATE, false);
  month   = RTC.get(DS1307_MTH,  false);
  year    = RTC.get(DS1307_YR,   false);
  year   += 15;
}

/*
 * Gets the latest timestamp and returns it format 'yyyy-mm-dd-hh.mn.ss'.
 * This format is DB2 timestamp format compatible, and it can be directly
 * moved to a register in the database.Returns the timestamp currently
 * set on the RTC.
*/
String RealTime::getDateTime(){
  readRTC();
  sprintf(ts, "%4d-%02d-%02d-%02d.%02d.%02d", year, month, day, hour, minute, second);
  return ts;
}
