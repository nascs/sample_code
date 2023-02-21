#include "wiringx.h"
#include "tm1637.h"
#include <stdio.h>

#define CLK 29
#define DIO 28

#define CMD_AUTOINCREASE 0x40
#define CMD_STARTADDRESS 0xC0
#define CMD_BRIGHTNESS 0x8F

void delay(unsigned int time) {
	int intime = time;
	while(intime--){
		for(int i=255;i>0;i--){ }
	}
}

void writeData(unsigned char data) {
	unsigned char indata = data;
	for(int i=0;i<8;i++){
		digitalWrite(CLK,LOW);
		delay(1);
		if((indata & 0x01) == 0x01) {
			digitalWrite(DIO,HIGH);
			delay(1);
		}else {
			digitalWrite(DIO,LOW);
			delay(1);
		}
		printf("0x%02x\t",indata);
		indata = (indata >> 1);
		digitalWrite(CLK,HIGH);
		delay(1);
	}
	printf("\n");
	digitalWrite(CLK,LOW);
	delay(1);
	digitalWrite(CLK,HIGH);
	delay(1);
	digitalWrite(CLK,LOW);
	delay(1);
}

void startDisplay() {
	digitalWrite(CLK,HIGH);
	delay(1);
	digitalWrite(DIO,HIGH);
	delay(1);
	digitalWrite(DIO,LOW);
	delay(1);
	digitalWrite(CLK,LOW);
	delay(1);
}

void stopDisplay() {
	digitalWrite(CLK,LOW);
	delay(1);
	digitalWrite(DIO,LOW);
	delay(1);
	digitalWrite(CLK,HIGH);
	delay(1);
	digitalWrite(DIO,HIGH);
	delay(1);
}

void display() {
	startDisplay();writeData(CMD_AUTOINCREASE);stopDisplay();
	startDisplay();writeData(CMD_STARTADDRESS);
    writeData(data[1]);
    writeData(data[0]);
    writeData(data[2]);
    writeData(data[4]);
	stopDisplay();
	startDisplay();writeData(CMD_BRIGHTNESS);stopDisplay();
}

int main() {
	if(wiringXSetup("rock4", NULL) == -1) {
        printf("failed to initialize rock4\n");
        return -1;
    }

	pinMode(CLK,PINMODE_OUTPUT);
	pinMode(DIO,PINMODE_OUTPUT);
	digitalWrite(CLK,LOW);
	digitalWrite(DIO,LOW);

	display();
	
	return 0;
}
