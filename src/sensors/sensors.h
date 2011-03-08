/**
Filename:	sensors.cpp

This, along with sensors.cpp, will hold functionality for talking to our motor controllers.

Log:	2011 Feb 25 - document created by Andrew Elias
	2011 Feb 29?- screwed up by somebody? contains execution.cpp contents
	2011 Mar 5  - fixed by Andrew Elias

TODO list:
	

*/

#ifndef _SENSORS_H_
#define _SENSORS_H_

class SensorSet {
	public:
		double getVoltage();
		bool isCharging();
		bool isCharged();
		double voltageDerivative();
};

#endif
