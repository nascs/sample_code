#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "wiringx.h"

typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;

uint32 databuf;

char *usage =
	"Usage: %s platform dht_pin\n"
	"Example: %s rock4 8\n";

void dht_init(int dht_pin) {
	pinMode(dht_pin, PINMODE_OUTPUT);
	digitalWrite(dht_pin, 1);
	
	sleep(1);

	return;
}

void host_init(int dht_pin) {	
	pinMode(dht_pin, PINMODE_OUTPUT);
	digitalWrite(dht_pin, 0);

	usleep(25000);

	digitalWrite(dht_pin, 1);
	pinMode(dht_pin, PINMODE_INPUT);
	delayMicroseconds(27);
	
	return;
}

uint8 read_data(int dht_pin) {
	uint8 crc, i;
	
	if (0 == digitalRead(dht_pin))
	{
		while(!digitalRead(dht_pin));
		
		for (i = 0; i < 32; i++)
		{
			while(digitalRead(dht_pin));
			while(!digitalRead(dht_pin));
			
			delayMicroseconds(32);
			
			databuf *= 2;
			
			if (digitalRead(dht_pin) == 1)
			{
				databuf++;
			}
		}
		
		for (i = 0; i < 8; i++) {
			while (digitalRead(dht_pin));
			while (!digitalRead(dht_pin));
			
			delayMicroseconds(32);
			
			crc *= 2;  
			if (digitalRead(dht_pin) == 1) {
				crc++;
			}
		}
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char *argv[]) {
	char *str = NULL, *platform = NULL;
	char usagestr[130];
	int invalid = 0;

	memset(usagestr, '\0', 130);

	// expect only 1 argument => argc must be 2
	if(argc != 3) {
		snprintf(usagestr, 129, usage, argv[0], argv[0]);
		puts(usagestr);
		return -1;
	}

	platform = argv[1];
	str = argv[2];
	while(*str != '\0') {
		if(!isdigit(*str)) {
			invalid = 1;
		}
		str++;
	}
	if(invalid == 1) {
		printf("%s: Invalid dht pin %s\n", argv[0], argv[2]);
		return -1;
	}

	if(-1 == wiringXSetup(platform, NULL)) {
		printf("Setup WiringX failed!\n");
		
		return 1;
	}
	
	while(1) {
		dht_init(atoi(argv[2]));
		
		host_init(atoi(argv[2]));
	 
		if(read_data(atoi(argv[2]))) {
			printf("RH:%d.%d\n", (databuf >> 24) & 0xff, (databuf >> 16) & 0xff); 
			printf("TMP:%d.%d\n", (databuf >> 8) & 0xff, databuf & 0xff);
			printf("\n");
		
			databuf = 0;
		} else {
			printf("Sensor dosent ans!\n");
			databuf = 0;
		}
		
		sleep(1);
	}
	
	return 0;
}
