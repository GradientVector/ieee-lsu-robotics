/**
[TODO: Documentation goes here]

author - Del Spangler
*/

#include "serial.h"

serial::serial() {
    fd = -1;
}

serial::serial(const char *portName, int baud) {
    serial();
    openPort(portName,baud);
}

serial::~serial() {
    closePort();
}

int serial::openPort(const char *portName, int baud) {
    if (fd > 0) closePort();
    fd = open(portName, O_RDWR | O_NOCTTY | O_NONBLOCK );
    if (fd < 0) throw serial_exception("Error opening serial port\n");
    
    bzero(&tio,sizeof(tio));
    serial::selectBaudRate(baud);
    tio.c_iflag = IGNPAR;
    tio.c_oflag = 0;
    tio.c_lflag = 0;
    tio.c_cc[VTIME] = 1; // inter-character timer used
    tio.c_cc[VMIN] = 1; //blocking read until 1 read

    tcflush(fd,TCIFLUSH);
    tcsetattr(fd,TCSANOW,&tio);
}

int serial::closePort() {
    close(fd);
    fd = -1;
}

int serial::recv(char *buf, int size, bool blocking = false) {
    int x = 0;
    if (fd < 0) throw serial_exception("File descriptor has not been opened.\n");
    if (blocking) 
        while (x == 0) { usleep(10000); x=read(fd,buf,size); }
    else
        x = read(fd,buf,size);
    return x;
}

int serial::send(char *buf, int size = -1,bool blocking = true) {
    int temp = size<0?strlen(buf):size;
    int x = 0;
    if (fd < 0) throw serial_exception("File descriptor has not been opened.\n");
    if (blocking)
        while (x != temp) x+=write(fd,&buf[x],temp-x); 
    else
        x = write(fd,buf,temp);
    return x;
}

void serial::selectBaudRate(int baud) {
    switch (baud) {
        case 115200:
        default:
            tio.c_cflag = B115200 | CRTSCTS | CS8 | CLOCAL | CREAD;
    }
}
