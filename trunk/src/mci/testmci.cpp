#include "mci.h"


#define DEBUG 

#define baudRate 115200

int main()
{
	double Kp, Ki, Kd;
	unsigned int P, I, D, Q, T;
	int modeCode;
	char mode[15];

	unsigned int T;
	double vel[2];
	double enc[2];

	char portName[15];        
	unsigned int portNumber = 0;
	sprintf(portName, "/dev/ttyUSB%u", portNumber);


        MCI mc();   // Creates an instance of the MCI class
	Serial io(portName,baudRate); //creats an instance of the serial class

	if (!io.isOpen()) {printf("fail to establish COM link\n"); return -1;}
	
	printf("COM link establish with %c\n", portName);
	
//reset mc status
	mc.resetEncoder();
	mc.resetPID();

//get current mc stauts
	mc.getOperationMode(modeCode);
	switch(mode){
		case 1: mode = "Open Loop Mode"; 
			break;
		case 2: mode = "Velocity Controlled Mode"; 
			break;
		case 3: mode = "Position Controlled Mode"; 
			break;
		default: mode = "ERROR";
			break;
	}
	printf("Current Operation Mode = %c", mode);
	mc.getEncVal(enc[0],enc[1]);
	printf("Current Encoder Value: left = %d, right = %d",enc[0], enc[1]);
//get Velocity Loop Values
	mc.getPIDVal("V", P, I, D, Q);
	pritnf("Controller Value for Velocity Loop: P = %d, I = %d, D = %d, Q = %d", P, I, D, Q);
	mc.getRealPIDVal("V", Kp, Ki, Kd);
	pritnf("Controller Gain for Velocity Loop: Kp = %d, Ki = %d, Kd = %d, Kq = %d", Kp, Ki, Kd, Kq);
	mc.getUpdatePeriod("V", T);
	pritnf("Controller Update Period = %d",T);

//get Position Loop Values
	mc.getPIDVal("P", P, I, D, Q);
	pritnf("Controller Value for Position Loop: P = %d, I = %d, D = %d, Q = %d", P, I, D, Q);
	mc.getRealPIDVal("P", Kp, Ki, Kd);
	pritnf("Controller Gain for Position Loop: Kp = %d, Ki = %d, Kd = %d, Kq = %d", Kp, Ki, Kd, Kq);
	mc.getUpdatePeriod("P", T);
	pritnf("Controller Update Period = %d",T);;
	
//determin the which which H-bridge is for right and which H-bridge is for left
//wheel 1
	mc.resetEncoder();
	mc.setVelocity(10,0);
	mc.getEncVal(enc[0],enc[1]);
	if(enc[0]>enc[1])printf("enc[0] is associate with the wheel thats turning right now");
	else printf("enc[1] is associate with the wheel thats turning right now");
	pritnf("for function setVelocity(a,b) 'a' is associated with the wheel that's turning right now");
	mc.setVelocity(0,0);
//wheel 2
	mc.setVelocity(0,10);
	mc.getEncVal(enc[0],enc[1]);
	if(enc[0]>enc[1])printf("enc[0] is associate with the wheel thats turning right now");
	else printf("enc[1] is associate with the wheel thats turning right now");
	pritnf("for function setVelocity(a,b) 'b' is associated with the wheel that's turning right now");	
	mc.setVelocity(0,0);



//set PID Value... run PID calibration program 

	
	


