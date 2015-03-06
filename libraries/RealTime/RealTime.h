/*===============================================================
 *  Module   : RealTime.h
 *  Author   : Julio Cesar Torres (juliozohar@gmail.com) 
 *  Type     : Header FILE
 *  Date     : 07/04/2014
 *  Objective: Library for using Real Time Clock (RTC), based on 
 *             an implementation on the DS1307 integrated circuit. 
 *             Header file, definitions used in program. 
 *===============================================================
 *  (C) 2014 Licensed under CERN OHL v.1.2
 *===============================================================
 */
 #ifndef RealTime_h
 #define RealTime_h
 #include "Arduino.h"

 
 class RealTime{
   
   public: 
   
     RealTime(); 
     char ts[20];
     void start();
     void stop();
     void setDateHour(int year, int month, int day,
        int hour, int minute, int second, int day_week);
     void readRTC();
     String getDateTime();

 };
 
 typedef struct ts {
   int ts_year;
   int ts_month;
   int ts_day;
   int ts_hour;
   int ts_minute;
   int ts_second;
 } TIMESTAMP; 

#endif