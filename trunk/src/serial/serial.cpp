/**
[TODO: Documentation goes here]
.cpp file for the serial comm class
author - Del Spangler
*/

#include "serial.h"

Serial::Serial() {
    fd = -1;
}

Serial::Serial(const char *portName, int baud) {
    Serial();
    openPort(portName,baud);
}

Serial::~Serial() {
    closePort();
    fd = -1;
}

int Serial::openPort(const char *portName, int baud) {
    if (fd > 0) closePort();
    fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY );
    if (fd < 0) throw serial_exception("Error opening serial port\n");
    
    tcgetattr(fd,&tio);
    //bzero(&tio,sizeof(tio));
    Serial::selectBaudRate(baud);
    tio.c_iflag = IGNPAR;
    tio.c_oflag = 0;
    tio.c_lflag = 0;
    tio.c_cc[VTIME] = 0; // inter-character timer used
    tio.c_cc[VMIN] = 0; //blocking read until 1 read
    tcsetattr(fd,TCSANOW,&tio);
    tcflush(fd,TCIFLUSH);
    return 0;
}

bool Serial::isOpen() {
    if (fd != -1) return true;
    return false;
}

int Serial::closePort() {
    close(fd);
    fd = -1;
    return 0;
}

int Serial::recv(char *buf, int size, bool blocking) {
    int x = 0;
    if (fd < 0) throw serial_exception("File descriptor has not been opened.\n");
    if (blocking) 
        while (x == 0) { 
		usleep(10000); 
		x=read(fd,buf,size); 
	}
    else
        x = read(fd,buf,size);
    return x;
}

int Serial::send(char *buf, int size,bool blocking) {
    int temp = size<0?strlen(buf):size;
    int x = 0;
    if (fd < 0) throw serial_exception("File descriptor has not been opened.\n");
    if (blocking)
        while (x != temp) x+=write(fd,&buf[x],temp-x); 
    else
        x = write(fd,buf,temp);
    return x;
}

void Serial::selectBaudRate(int baud) {
    switch (baud) {
        case 57600:
        default:
            tio.c_cflag = B57600 | CS8 | CLOCAL | CREAD;
            tio.c_ospeed = B57600;
            tio.c_ispeed = B57600;
            cfsetispeed(&tio,B57600);
            cfsetospeed(&tio,B57600);
    }
}
