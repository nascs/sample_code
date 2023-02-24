#include <stdio.h>
#include <unistd.h>
#include "wiringx.h"

int main () {

    int button = 9;
    int led = 8;

    if(wiringXSetup("rock4", NULL) == -1) {
        printf("wiringXSetup failed ...\n");
        return -1;
    }

    pinMode(led, PINMODE_OUTPUT);
    pinMode(button, PINMODE_INPUT);

    while(1) { 
        if(digitalRead(button) == 0){   
            sleep(0.2);
            if(digitalRead(button) == 0) {   
                digitalWrite (led, LOW);    
            } 
        } else { 
            digitalWrite (led, HIGH);
        }
    }

    return 0;
}