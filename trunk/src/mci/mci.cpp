#include "mci.h"

//communication scheme
//using the same scheme as last year
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



//The following line is not currently in use:
//#define DEBUG

// default constructor
// default values = 0 for now

MCI::MCI()
{ io = new Serial();
  modeStatus = 0;
  loopStatus = 0;
}         


//constructor with given portname and baudrate
MCI::MCI(const char *portName,int baudRate){

}


//destructor
MCI::~MCI(){ 
  if(io->isOpen()) io->closePort();
  resetEncoders();
  resetPID();
}

//TODO: this is wrong; can't just call destructors and constructors like this
void MCI::reset(){
   if(io->isOpen()) io->closePort();
  resetEncoders();
  resetPID();
  MCI();
}


// sends message to reset the encodes
void MCI::resetEncoders(){ 
   char buf[255];
   sprintf(buf,"!C\n");
   io.send(buf);
   return 0;
}
     
// gets the values of the encoders
void MCI::getEncVal(double left,double right){
   char buf[255];
   char pos_0[255];
   char pos_1[255];
   sprintf(buf,"?E\n");
   io.send(buf);
   io.recv(buf);
   left = atoi(pos_0);
   io.recv(buf);
   right = atoi(pos_1);
   return 0;
}

//reset PID
void MCI::resetPID(){
   char buf[255];
   sprintf(buf,"!F\n");
   return 0;
}

// gets the current pid values
// send command to  mc to send the pid values
// assign the values to P I D
void MCI::getPIDVal(const char *mode, unsigned int P, unsigned int I, unsigned int D, unsigned int Q){
   char buf[255];
   int status = 0;
   int Q = 0;

   sprintf(buf,"?G%c\n",mode);
   io.sent(buf);

   io.recv(buf);
   status = atoi(buf);
   if (status != 0) return -1;

   io.recv(buf);
   *P = atoi(buf);
   io.recv(buf);
   *I = atoi(buf);
   io.recv(buf);
   *D = atoi(buf);
   io.recv(buf);
   *Q = atoi(buf);

   return 0;
}

void MCI::getRealPIDVal(const char *mode, double Kp, double Ki, double Kd){
   unsigned int P, I, D, Q;
   getPIDVal(mode, P, I, D, Q);
   Kp = (double) P << Q;
   Ki = (double) I << Q;
   Kd = (double) D << Q;
   return 0;
}
// sends message to set the pid values
void MCI::setPIDVal(const char *mode, unsigned int *P, unsigned int *I, unsigned int *D, unsigned int *Q){
  char buf[255];

  sprintf(buf, "!G%c%08u%08u%08u%02u\n", mode, P, I, D, Q );
  io.sent(buf);
}


// send command to mc to send the loop status
// openloop = 0, closedloop = 1
// return 0 or 1
void MCI::getOperationMode(int mode){
   char buf[255];
   int status = 0;
   int mode = 0;
   
   sprintf(buf, "?M\n");
   io.send(buf);
   io.recv(buf);
   status = atoi(buf);
   if (status !=0) return -1;
   io.recv(buf);
   mode = atoi(buf);
   return mode;

}

// sends commant to mc to set the operationMode (open loop, velocity control, position control). pass '1' for our purposes
void MCI::setOperationMode(int mode){
   char buf[255];
   sprintf(buf, "!M%d", mode);
   io.send(buf);
   return 0;
}

// get loop update period 
void MCI::getUpdatePeriod(const char *mode, unsigned int T){
   char buf[255];
   sprintf(buf, "?T%c\n",mode);
   io.send(buf);
   io.recv(buf);
   T = atoi(buf);
   return 0;
}

// set loop update period 
void MCI::setUpdatePeriod(const char *mode, unsigned int *T){
   char buf[255];
   sprintf(buf, "!T%c%08u", mode, T);
   io.send(buf);
   return 0;
}


// sends command to mc to set the velocity of the
// left and right wheels (a,b)
// inputs: max accepted values are  9999, indicating maximum speed.
//         min accepted values are -9999, indicating maximum reverse speed.  
void MCI::setVelocity(double a, double b){
   char buf[255];
   sprintf(str, "!V%c%04d%c%04d\n",(a<0.0)?'-':'+',abs(a),(b<0.0)?'-':'+',abs(b));
   io.send(buf);
}

//gets the current velocity from the encoders data
//outputs, via return parameters, #s between -9999 and 9999 
void MCI::getVelocity(int a, int b){
   char buf[255];
   char temp[4];
   int status;
   sprintf(buf, "?V\n");
   io.send(buf);
   io.recv(buf);
   status = atoi(buf);
   if (status !=0) return -1;
   io.recv(buf);
   temp[0]=buf[1];
   temp[1]=buf[2];
   temp[2]=buf[3];
   temp[3]=buf[4];
   a = atoi(temp);
   if (buf[1] == '-') a = a *-1;
   io.recv(buf);
   temp[0]=buf[1];
   temp[1]=buf[2];
   temp[2]=buf[3];
   temp[3]=buf[4];
   b = atoi(temp);
   if (buf[1] == '-') b = b *-1;

}

