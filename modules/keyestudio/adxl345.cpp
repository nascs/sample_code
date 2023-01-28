#include <iostream>
#include <thread>
#include <chrono>
#include "wiringx.h"

#define DEVICE_ID 0x53
#define REG_POWER_CTL   0x2D
#define REG_DATA_X_LOW  0x32
#define REG_DATA_X_HIGH 0x33
#define REG_DATA_Y_LOW  0x34
#define REG_DATA_Y_HIGH 0x35
#define REG_DATA_Z_LOW  0x36
#define REG_DATA_Z_HIGH 0x37

int main(int argc, char **argv) {
    int fd;

    // Setup wiringX
    if(wiringXSetup((char*)"rock4", NULL) == -1) {
        std::cout << "wiringX setup failed ...\n";
        return -1;
    }
    // Setup I2C communication
    if((fd = wiringXI2CSetup("/dev/i2c-7",0x53)) == -1) {
        std::cout << "wiringXI2CSetup failed ...\n";
        return -1;
    }

    std::cout << "I2C communication successfully setup.\n";
    // Switch device to measurement mode
    wiringXI2CWriteReg8(fd, REG_POWER_CTL, 0b00001000);
    while(1) {
        int dataX = wiringXI2CReadReg16(fd, REG_DATA_X_LOW);
        dataX = -(~(int16_t)dataX + 1);
        int dataY = wiringXI2CReadReg16(fd, REG_DATA_Y_LOW);
        dataY = -(~(int16_t)dataY + 1);
        int dataZ = wiringXI2CReadReg16(fd, REG_DATA_Z_LOW);
        dataZ = -(~(int16_t)dataZ + 1);
        std::cout << "x: " << dataX << ", y: " << dataY << ", z: " << dataZ << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}