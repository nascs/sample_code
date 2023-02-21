#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "wiringx.h"

#define gpio 8

int main(int argc, char *argv[]) {

	if(wiringXSetup("rock4", NULL) == -1) {
		wiringXGC();
		return -1;
	}
	pinMode(gpio, PINMODE_OUTPUT);

	while(1) {
		digitalWrite(gpio, HIGH);
		sleep(1);
		digitalWrite(gpio, LOW);
		sleep(1);
	}

	return 0;
}
