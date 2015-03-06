==============================================
   RealTime for Arduino Libary, version 1.0 
==============================================

Usage
-----

This library supports the following devices : 

DS1307, DS1317 and DS1307Z 

Please, verify in the device datasheet the reference circuit 
to use with this library. 

This library requires the use of a I2C protocol, and it can 
only be used with any other device that also supports it. 

The functions implemented in this version are: 

		- setDateTime(); 
Sets a timestamp in the clock, in the format yyyy-mm-dd-hh.mn.ss; 

		- getDate(); 
		Returns the timestamp currently running in the RTC

		- stop(); 
		Stops and resets the data in internal storage

		- start(); 
		Starts a time counting cycle

Note that to keep the timestamp after powering off the circuit, 
you will need to use a backup battery, in the 3rd and 4th pins 
of your DS13xx CI. 



Change history
--------------

2015-01-10 First version. 



Credits 
-------

The RealTime library was derived from the DS1307 library.

Jules-Caesar Toussaint <juliozohar@gmail.com> originally developed 
this library. 

You can get the latest version of the library in the Github 
repository <http://github.com/juliozohar>. 



License
-------

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA