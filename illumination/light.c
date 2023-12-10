#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <pthread.h>

#define SLAVE_ADDR_01 0x48  // 조도센서 슬레이브 주소

static const char* I2C_DEV = "/dev/i2c-1";  // I2C 연결 장치 파일
int i2c_fd;
const int adcChannel = 0;

int brightness = 0;
pthread_mutex_t lock_brightness;

int light_init() {
    pthread_mutex_init(&lock_brightness, NULL);
    if ((i2c_fd = wiringPiI2CSetupInterface(I2C_DEV, SLAVE_ADDR_01)) < 0) {
        // perror("wiringPiI2CSetup Failed\n")
        return 1;
    }
    
    return 0;
}

int getBrightness() {
    int preVal, curVal;

    pthread_mutex_lock(&lock_brightness);

    wiringPiI2CWrite(i2c_fd, 0x40 | adcChannel);
    preVal = wiringPiI2CRead(i2c_fd);
    curVal = wiringPiI2CRead(i2c_fd);

    pthread_mutex_unlock(&lock_brightness);

    return curVal;
}