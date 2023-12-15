#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <softTone.h>
#include <wiringPiI2C.h>
#include <wiringSerial.h>

// global variable
pthread_mutex_t mtx;
unsigned char settingTime[5] = {'1', '5', '0', '7', '\0'};
//int sec, min, hour, day, date, month, year;

void main()
{
    // variable space
    unsigned char mainTime[5];
    unsigned char resetTime[5] = {'9', '9', '9', '9', '\0'};

    // set up
    if (wiringPiSetupGpio() == -1)
        return;
    init_servo();
    init_speaker();
    i2c_setup();
    init_RTC();
    pthread_mutex_init(&mtx, NULL);

    // main proccess
    pthread_create(&bluetooth, NULL, bluetoothThread, NULL);
    while (1)
    {
        print_time();
        convertTime(hour, min, mainTime);
        if (strcmp(mainTime, settingTime) == 0)
        {
            printf("!!!!!!alarm!!!!!!!\n");
            strcpy(mainTime, resetTime);
            pthread_create(&servomotor, NULL, onSwitch, NULL);
            pthread_create(&speaker, NULL, start_alarm, NULL);
            delay(2400);
            pthread_cancel(servomotor);
            pthread_cancel(speaker);
            break;
        }
    }

    // exit proccess
    pthread_cancel(bluetooth);
    pthread_mutex_destroy(&mtx);
    return;
}
