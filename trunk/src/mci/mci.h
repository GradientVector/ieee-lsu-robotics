/**
Filename:	mci.h
	
Motor Controller Interface. this gives us the ability to actually perform physical actions.
*/

#ifndef _MCI_H_
#define _MCI_H_

#include "../serial/serial.h"
//TODO remove? #include <math.c>
#include <math.h>
#include <stdio.h>

//communication scheme
/*
  !B - turn on/off encoder monitoring (with period in MCU ticks)
  !C - reset encoder position counters
  !F - reset PID states
  !G - set PID controller parameters (Kp,Ki,Kv,& Q)
  !M - set operation mode (0-Open Loop,1-Velocity Loop,2-Position Loop)
  !R - reset the MCU state
  !T - set loop update period (in ticks)
  !V - set short loop commands (for velocity loop)

  ?E - get encoder values
  ?G - get PID controller parameters (Kp,Ki,Kv,& Q)
  ?M - get operation mode (0-Open Loop,1-Velocity Loop,2-Position Loop)
  ?T - get loop update period (in ticks)
  ?V - get short loop commands (for velocity loop)
*/

// default constructor
// default values = 0 for now

class MCI {
	protected:
		Serial * io;
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
        void setEncVal(int &left,int &right);
        
        void resetPID();
        void getPIDVal(const char *mode, unsigned int *P, unsigned int *I, unsigned int *D, unsigned int *Q);
        void setPIDVal(const char *mode, unsigned int *P, unsigned int *I, unsigned int *D, unsigned int *Q);
        
        int  getOperationMode();
        void setOperationMode(int mode);

        void getUpdatePeriod(const char *mode, unsigned int *T);
        void setUpdatePeriod(const char *mode, unsigned int *T);

        void setVelocity(int *a, int *b);
        void getVelocity(int &a, int &b);
};

#endif
