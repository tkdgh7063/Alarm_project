#include "RTC.h"
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <sys/ioctl.h>
#include <time.h>

static const char* I2C_DEV = "dev/i2c-1";   // I2C 연결 장치 파일

int bcdToDec(int bcd) {
    return ((bcd / 16) * 10) + (bcd % 16);
}

int decToBcd(int dec) {
    return ((dec / 10) * 16) + (dec % 10);
}

// int decimalToBinary(int value){
//     int binary = (((value/10)<<4) + (value%10));
//     return binary;
// }

// int binaryToDecimal(int value){
//     int decimal = ((value&240)>>4)*10 + (value&15);
//     return decimal;
// }

int RTC_init() {
    // 초기 날짜 초기화
    // 성공 시 0, 실패 시 1 반환
    pthread_mutex_init(&lock_time, NULL);
    rtc_fd = wiringPiI2CSetupInterface(I2C_DEV, SLAVE_ADDR_02);
    if (rtc_fd == -1) {
        return 1;
    }

    // 현재 시간
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);

    // 시간 설정
    wiringPiI2CWriteReg8(rtc_fd, SEC_ADDR, decToBcd(now->tm_sec));
    wiringPiI2CWriteReg8(rtc_fd, MIN_ADDR, decToBcd(now->tm_min));
    wiringPiI2CWriteReg8(rtc_fd, HOUR_ADDR, decToBcd(now->tm_hour));

    return 0;
}

int getSec() {
    pthread_mutex_lock(&lock_time);
    int sec = bcdToDec(wiringPiI2CReadReg8(rtc_fd, SEC_ADDR));
    pthread_mutex_unlock(&lock_time);
    
    return sec;
}

int getMin() {
    pthread_mutex_lock(&lock_time);
    int min = bcdToDec(wiringPiI2CReadReg8(rtc_fd, MIN_ADDR));
    pthread_mutex_unlock(&lock_time);
    
    return min;
}

int getHour() {
    pthread_mutex_lock(&lock_time);
    int hour = bcdToDec(wiringPiI2CReadReg8(rtc_fd, HOUR_ADDR));
    pthread_mutex_unlock(&lock_time);
    
    return hour;
}