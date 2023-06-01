#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mraa/i2c.h"



#define I2C_BUS 2
#define LED_ADDRESS 0x20

volatile sig_atomic_t flag = 1;

void sig_handler(int signum) {
    if (signum == SIGINT) {
        fprintf(stdout, "Exiting...\n");
        flag = 0;
    }
}



int main() {
    mraa_result_t status = MRAA_SUCCESS;
    mraa_i2c_context i2c;

    signal(SIGINT, sig_handler);
    mraa_init();

    i2c = mraa_i2c_init(I2C_BUS);
    if (i2c == NULL) {
        fprintf(stderr, "Failed to initialize I2C\n");
        mraa_deinit();
        return EXIT_FAILURE;
    }

    /* set slave address */
    status = mraa_i2c_address(i2c, LED_ADDRESS);
    if (status != MRAA_SUCCESS) {
        return -1;
    }
    
    while(1) {

        /**
         * Write a single word to an i2c context
         *
         * @param dev The i2c context
         * @param data The word to write
         * @param command The register
         * @return Result of operation
         */
        mraa_i2c_write_byte_data(i2c, 0x23, 0x08);
        sleep(1);
        mraa_i2c_write_byte_data(i2c, 0x21, 0x01);
        sleep(1);
        mraa_i2c_write_byte_data(i2c, 0x33, 0x12);
        sleep(1);
        mraa_i2c_write_byte_data(i2c, 0x1f, 0x42);
        sleep(1);
    }

    return 0;
}
