/**
Filename:	mci.h
	
Motor Controller Interface. this gives us the ability to actually perform physical actions.

Log:	

*/

#ifndef _MCI_H_
#define _MCI_H_

#include "serial.h"
#include "math.c"

//communication scheme
// se = reset ecnoders
// ge = get encoder values
// sp = set pid values
// gp = get pid values
// sv = set velocity
// gv = get valocity

// default constructor
// default values = 0 for now

class MCI {
	protected:
		Serial *io;
		int modeStatus;
		int loopStatus;	
		float P,I,D;
	public:
		enum { OPEN_LOOP, CLOSED_LOOP };
		enum { MIXED_MODE, STANDARD_MODE };

		MCI();
		MCI(const char *portName,int baudRate);
		~MCI();
		void reset();
		void resetEncoders();
		void getEncVal(int &left,int &right);
    void getEncVal(int &left,int &right);
    void resetPID();
    void getPIDVal(const char *mode, unsigned int *P, unsigned int *I, unsigned int *D, unsigned int *Q);
    void setPIDVal(const char *mode, unsigned int *P, unsigned int *I, unsigned int *D, unsigned int *Q);
    int getOperationMode();
    void setOperationMode(int mode);
    void getUpdatePeriod(const char *mode, unsigned int *T);
    void setUpdatePeriod(const char *mode, unsigned int *T);
    void setVelocity(int *a, int *b);
    void getVelocity(int &a, int &b);
};

#endif
