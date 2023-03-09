#include "wiringx.h"
#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int main(int argc, char *argv[]) {

    int pat = 200;
    int rotation = 300;
    int servo = 2;
    int angle  = 0;

    if(argc != 2) {
        printf("numer of param you input is %d, please input two param !\n", argc);
        printf("example: sudo ./a.out 90, \n");
        return -1;
    }

    angle = atoi(argv[1]);

    // get the true angle
    if(angle<=180 && angle>=0){
        rotation = 40+10*angle;
    } else {
        printf("your angle is out of range !\n");
        printf("angle range: [0,180] \n");
        return -1;
    }

    if(angle < 45){
        pat = 500;
    }
    if(wiringXSetup("rock4", NULL) == -1) {
        printf("wiringX setup on rock4 failed !\n");
        return -1;
    }

    pinMode(servo, PINMODE_OUTPUT) ;
    
    for (int i = 0; i < pat; i++) {
        digitalWrite(servo, HIGH);
        usleep(rotation);
        digitalWrite(servo, LOW);
        delayMicroseconds(2500-rotation);
    }

	printf("angle is %d, great! Please reset your servo.\n", angle);

	return 0;
}

