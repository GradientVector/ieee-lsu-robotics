#ifndef SERIAL
#define SERIAL

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
        int openPort(const char *portName, int baud);
        int closePort();
        int recv(char *buf,int size,bool blocking);
        int send(char *buf,int size,bool blocking);
};
#endif
