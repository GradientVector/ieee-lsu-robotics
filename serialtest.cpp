#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "serial.h"

using namespace std;

int main() {
	char buf[255];
	int size = 0;
	serial io("/dev/ttyUSB0",115200);
	if (!io.isOpen()) return -1;
	sprintf(buf,"Echo test\n");
	size = io.send(buf,-1,true);
	sprintf(buf,"");
	printf("%d bytes sent over serial.\n",size);
	size = io.recv(buf,255,true);
	printf("%d bytes received back.\n",size);
	printf("Msg: %s",buf);
	return 0;
}
