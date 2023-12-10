#ifndef RTC_H
#define RTC_H

#include <pthread.h>

#define SLAVE_ADDR_02 0x68

#define SEC_ADDR 0x00
#define MIN_ADDR 0x01
#define HOUR_ADDR 0x02

extern pthread_mutex_t lock_time;
extern int rtc_fd;

int bcdToDec(int bcd);
int decToBcd(int dec);
int RTC_init();
int getSec();
int getMin();
int getHour();

#endif // RTC_H