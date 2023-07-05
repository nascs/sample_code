#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    
    int fd = 0;
    char buf[32];

    if((fd = open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw", O_RDONLY)) < 0) {
        printf("Failed to open IIO device");
        return -1;
    }

    ssize_t numRead = read(fd, buf, sizeof(buf)-1);
    if (numRead < 0) {
        perror("Failed to read IIO device");
        close(fd);
        return -1;
    }
    buf[numRead] = '\0';

    close(fd);

    int value = atoi(buf);
    printf("IIO device value: %d\n", value);

    return 0;
}
