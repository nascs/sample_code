#include <iostream>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "mraa/common.hpp"
#include "mraa/i2c.hpp"


#define I2C_BUS 0
#define LED_ADDRESS 0x20

volatile sig_atomic_t flag = 1;

void sig_handler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Exiting..." << std::endl;
        flag = 0;
    }
}

int main() {
    signal(SIGINT, sig_handler);

    mraa::I2c i2c(I2C_BUS);
    i2c.address(0x20);

    while (flag) {
        i2c.writeReg(0x21, 0x01);
        usleep(100000);
        i2c.writeReg(0x20, 0x08);
        usleep(100000);
    }

    return EXIT_SUCCESS;
}
