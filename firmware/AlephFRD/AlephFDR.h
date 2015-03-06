/*===============================================================
* Aleph Flight Data Recorder v.001a
* Module  : AlephFDR.h
* Type    : C Header 
* Author  : Julio Cesar Torres 
* Date    : December 23rd 2014 
* Remarks : Read and register timestamp (DS1307) and internal 
*           temperature (LM35). 
*================================================================
* (C) 2014 Licensed under CERN OHL v.1.2
*================================================================
*/

#define CAL_OFFSET_LM35         0
#define IO_PIN_TEMP_INT 	A0
#define CAL_OFFSET_LM35 	-2
#define VERSION 		"1.0.0a"
#define REG_TYPE 		"01" 
#define REG_NAME 		"F001A"
#define DELAY_TIME		2000

float FAT_MULT_ANLG           = 0.09765625;

