/**
Filename:	mci.h
	
Motor Controller Interface. this gives us the ability to actually perform physical actions.

Log:	

*/

#ifndef _MCI_H_
#define _MCI_H_

#include "serial.h"

enum { MCI_OPEN_LOOP, MCI_CLOSED_LOOP };
enum { MCI_MIXED_MODE, MCI_STANDARD_MODE };

class MCI {
	protected:
		Serial *io;
		int modeStatus;
		int loopStatus;	
		float P,I,D;
	public:
		MCI();
		MCI(const char *portName,int baudRate);
		~MCI();
		void reset();
		void resetEncoders();
		void getEncVal(int &left,int &right);
		void setPIDVal(float P, float I, float D);
		void getPIDVal(float &P, float &I, float &D);
		void setLoopStatus(int status);
		int getLoopStatus();
		void setModeStatus(int status);
		int getModeStatus();
		void setVelocity(int a, int b);
		void getVelocity(int &a, int &b);
		
};

#endif
