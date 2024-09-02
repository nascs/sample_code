#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "wiringx.h"

#define ADDR 0x3c

int main() {
    int fd = 0;
    int bytes_read = 0;
    int block_size = 32; // buffer size
    unsigned char write_block[32]; // write buffer
    unsigned char read_block[32]; // read buffer

	if(wiringXSetup("rock4", NULL) == -1) {
		printf("wiringXSetup failed ...\n");
		return -1;
	}
	if((fd = wiringXI2CSetup("/dev/i2c-7", ADDR)) == -1) {
		printf("wiringXI2CSetup failed ...\n");
		return -1;
	}

    // init write_block as 0
    for (int i = 0; i < block_size; i++) {
        write_block[i] = i;
    }

    if(wiringXI2CWriteBlockData(fd, ADDR, write_block, block_size) < 0) {
        printf("write error, exit\n");
        return -1;
    }

    //  int wiringXI2CReadBlockData(int, int, unsigned char*, int);
    bytes_read = wiringXI2CReadBlockData(fd, ADDR, read_block, block_size);

    if( bytes_read >= 0) {
        for (int i = 0; i < bytes_read; i++) {
            printf("0x%02x ", read_block[i]);
        }
        printf(" \t");
    } else {
        printf("read error \n");
        return -1;
    }

    printf("\n");

    return 0;
}
