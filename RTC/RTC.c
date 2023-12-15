#include "RTC.h"
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <sys/ioctl.h>
#include <time.h>

#define SLAVE_ADDR_01 0x68                 // 슬레이브 주소
static const char *I2C_DEV = "/dev/i2c-1"; // I2C 연결을 위한 장치 파일

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

//1차 발표 함수
// void init_RTC()
// {
//     // 시간 설정
//     wiringPiI2CWriteReg8(i2c_fd, 0x01, 0x06);        // 분
//     wiringPiI2CWriteReg8(i2c_fd, 0x02, 0x40 | 0x13); // 0x40 -> 24시간 체계
//     wiringPiI2CWriteReg8(i2c_fd, 0x03, 0x04);        // 요일
//     wiringPiI2CWriteReg8(i2c_fd, 0x04, 0x26);        // 날짜
//     wiringPiI2CWriteReg8(i2c_fd, 0x05, 0x10);        // 월
//     wiringPiI2CWriteReg8(i2c_fd, 0x06, 0x23);        // 년
// }

void print_time()
{
    // 24시간 체계, 매초 업뎃, 현재시각으로 변경.
    sec = wiringPiI2CReadReg8(i2c_fd, 0x00);  //%x 출력 그대로
    min = wiringPiI2CReadReg8(i2c_fd, 0x01);  //%x 출력 그대로
    hour = wiringPiI2CReadReg8(i2c_fd, 0x02); // - 0x40
    hour = hour - 0x40;
    day = wiringPiI2CReadReg8(i2c_fd, 0x03);   // 16진수에 따라 요일 선택
    date = wiringPiI2CReadReg8(i2c_fd, 0x04);  //%x 출력 그대로
    month = wiringPiI2CReadReg8(i2c_fd, 0x05); //%x 출력 그대로
    year = wiringPiI2CReadReg8(i2c_fd, 0x06);  //%x 출력 그대로
    system("clear");
    switch (day)
    {
    case 0x01:
        printf("20%x년 %x월 %x일 월요일 %x시 %x분 %x초, 알람 시각 : %s\n",
               year, month, date, hour, min, sec, settingTime);
        break;
    case 0x02:
        printf("20%x년 %x월 %x일 화요일 %x시 %x분 %x초, 알람 시각 : %s\n",
               year, month, date, hour, min, sec, settingTime);
        break;
    case 0x03:
        printf("20%x년 %x월 %x일 수요일 %x시 %x분 %x초, 알람 시각 : %s\n",
               year, month, date, hour, min, sec, settingTime);
        break;
    case 0x04:
        printf("20%x년 %x월 %x일 목요일 %x시 %x분 %x초, 알람 시각 : %s\n",
               year, month, date, hour, min, sec, settingTime);
        break;
    case 0x05:
        printf("20%x년 %x월 %x일 금요일 %x시 %x분 %x초, 알람 시각 : %s\n",
               year, month, date, hour, min, sec, settingTime);
        break;
    case 0x06:
        printf("\r20%x년 %x월 %x일 토요일 %x시 %x분 %x초, 알람 시각 : %s\n",
               year, month, date, hour, min, sec, settingTime);
        break;
    case 0x07:
        printf("20%x년 %x월 %x일 일요일 %x시 %x분 %x초, 알람 시각 : %s\n",
               year, month, date, hour, min, sec, settingTime);
        break;
    }
}

void convertTime(int hour, int min, unsigned char *result)
{
    pthread_mutex_lock(&mtx);
    unsigned char tempHourTen = (hour >> 4) & 0xF;
    unsigned char tempHour = hour & 0xF;
    unsigned char tempMinTen = (min >> 4) & 0xF;
    unsigned char tempMin = min & 0xF;
    sprintf(result, "%d%d%d%d", tempHourTen, tempHour, tempMinTen, tempMin);
    pthread_mutex_unlock(&mtx);
    delay(100);
}