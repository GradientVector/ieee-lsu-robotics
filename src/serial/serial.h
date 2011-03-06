/**
Basic serial communication class that handles the opening and closing of a serial port.
Allows for easy send/recv of data across the serial line. (/dev/ttyUSB0 for beagleboard)
author - Del Spangler
*/

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "serial_exception.h"

#define BUF_SIZE 255

class serial {
    protected:
        int fd;
        struct termios tio;
        void selectBaudRate(int baud);
    public:
        serial();
        serial(const char *portName, int baud);
        ~serial();
        virtual int openPort(const char *portName, int baud);
	bool isOpen();
        virtual int closePort();
        virtual int recv(char *buf,int size,bool blocking=false);
        virtual int send(char *buf,int size=-1,bool blocking=true);
};
#endif
