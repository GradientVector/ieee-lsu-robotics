#include "mci.h"

//communication scheme
// se = reset ecnoders
// ge = get encoder values
// sp = set pid values
// gp = get pid values
// sv = set velocity
// gv = get valocity

// default constructor
// default values = 0 for now
MCI::MCI()
{ *io = new Serial();
  modeStatus = 0;
  loopStatus = 0;
  P= 0;
  I= 0;
  D= 0;
  }         


//constructor with given portname and baudrate
MCI::MCI(const char *portName,int baudRate)
{  //if(!io.isOpen())
   io.openPort(portName, baudRate)
 }

//destructor
MCI::~MCI()
{ if(io.isOpen())
  io.closePort();
  }


void MCI::reset(){}



// sends message to reset the encoders
void MCI::resetEncoders()
{ char *buff = "se";
     io.send( buff, buff.size,
     }
     
     
     

// gets the values of the encoders
void MCI::getEncVal(int &left,int &right)
{
     
     
     }

// sends message to set the pid values
void MCI::setPIDVal(float P, float I, float D)
{
     
     }

// gets the current pid values
// send command to  mc to send the pid values
// assign the values to P I D
void MCI::getPIDVal(float &P, float &I, float &D)
{
     
     
     }

// sends commant to mc to set the loop status
void MCI::setLoopStatus(int status){}


// send command to mc to send the loop status
// openloop = 0, closedloop = 1
// return 0 or 1
int MCI::getLoopStatus()
{
    
    
    }

// sends commant to mc to set the mode status
void MCI::setModeStatus(int status)
{
     
     
     }


// send command to mc to send the mode status
// mixed mode = 0; standard mode =1
// return 0 or 1
int MCI::getModeStatus()
{
    
    
    }



// sends command to mc to set the velocity of the
// left and right wheels (a,b)
void MCI::setVelocity(int a, int b)
{
     
     
     }

//gets the current velocity from the encoders data
void MCI::getVelocity(int &a, int &b)
{
     
     
     }

