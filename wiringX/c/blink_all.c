#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "wiringx.h"

int main() {
	int gpios[] = {8, 9, 7, 0, 2, 3, 12, 13, 14, 30, 21, 22, 23, 24, 25, 29, 28, 27, 26, 31, 10, 6, 5, 4, 1, 15, 16};

	if(wiringXSetup("rock4", NULL) == -1) {
		wiringXGC();
		return -1;
	}

	for(int i = 0; i < sizeof(gpios)/ sizeof(gpios[0]); i++) {
		pinMode(gpios[i], PINMODE_OUTPUT);
	}

	while(1) {
		for(int i = 0; i < sizeof(gpios)/ sizeof(gpios[0]); i++) {
			digitalWrite(gpios[i], HIGH);
		}
		sleep(1);
		for(int i = 0; i < sizeof(gpios)/ sizeof(gpios[0]); i++) {
			digitalWrite(gpios[i], LOW);
		}
		sleep(1);
	}

	return 0;
}
