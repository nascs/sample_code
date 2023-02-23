#include <stdio.h>
#include <unistd.h>
#include "wiringx.h"

#define INA 0
#define INB 1

int main(void) {
	int i = 0;

	if(wiringXSetup("rock4", NULL) == -1) {
        printf("failed to initialize rock4\n");
        return -1;
    }
	
	pinMode(INA,PINMODE_OUTPUT);
	pinMode(INB,PINMODE_OUTPUT);

	while(1) {
		printf("INA high\n");
		digitalWrite(INA,HIGH);
		for(i = 0; i < 4; i++) {
			sleep(1);
		}

		printf("INA low\n");
		digitalWrite(INA,LOW);
		for(i = 0; i <4; i++) {
			sleep(1);
		}

		printf("INB high\n");
		digitalWrite(INB,HIGH);
		for(i = 0; i < 4; i++) {
			sleep(1);
		}

		printf("INB low\n");
		digitalWrite(INB,LOW);
		for(i = 0; i < 4; i++) {
			sleep(1);
		}
	}

	return 0;
}
