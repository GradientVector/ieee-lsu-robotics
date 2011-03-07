/* This program demostrates how to use the serial class */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "serial.h"

using namespace std;

int main() {
	char buf[255];
	int size = 0;
	Serial io("/dev/ttyUSB0",57600);
	if (!io.isOpen()) return -1;
  	sprintf(buf,"Echo test, checking maximum line length. Results so far are looking pretty good.\n");
	size = io.send(buf);
	memset(buf,0,sizeof(buf));
	usleep(10000);
	printf("%d bytes sent over serial.\n",size);
	size = io.recv(buf,255);
	printf("%d bytes received back.\n",size);
	printf("Msg: %s",buf);
	return 0;
}
