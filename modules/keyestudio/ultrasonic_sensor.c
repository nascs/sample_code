#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "wiringx.h"

#define Trig  8
#define Echo  9


float disMeasure(void) {
    struct timeval tv1;
    struct timeval tv2;
    long time1, time2;
    float dis;
    digitalWrite(Trig, LOW);
    usleep(2);
    digitalWrite(Trig, HIGH);
    usleep(10); //send out ultrasonic pulses

    while(!(digitalRead(Echo) == 1));
    gettimeofday(&tv1, NULL); 
    while(!(digitalRead(Echo) == 0));
    gettimeofday(&tv2, NULL);

    time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;
    time2 = tv2.tv_sec * 1000000 + tv2.tv_usec;

    dis = (float)(time2 - time1)/1000000 * 34000 / 2;

    return dis;
}

int main(void) {

    float dis;
    if(wiringXSetup("rock4", NULL) == -1) {
        printf("wiringXSetup failed ...\n");
        return -1;
    }
    pinMode(Echo, PINMODE_INPUT);
    pinMode(Trig, PINMODE_OUTPUT);

    while(1) {
        dis = disMeasure();
        printf("%0.2f cm\n", dis);
        sleep(1);
    }

    return 0;
}
