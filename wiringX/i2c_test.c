#include <stdio.h>
#include "wiringx.h"
#include <unistd.h>

int main() {

    int fd ;
    
    if(wiringXSetup("rock4", NULL) == -1) {
        printf("wiringXSetup failed ...\n");
        return -1;
    }
    if((fd = wiringXI2CSetup("/dev/i2c-7",0x20)) == -1) {
        printf("wiringXI2CSetup failed ...\n");
        return -1;
    }
    
    while(1) {
        wiringXI2CWrite(fd,0x5f);
        sleep(1);
        wiringXI2CWrite(fd,0x7f);
        sleep(1);
    }


    return 0;
}
