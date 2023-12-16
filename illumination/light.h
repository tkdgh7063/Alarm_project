#ifndef LIGHT_H
#define LIGHT_H

#include <pthread.h>

#define SLAVE_ADDR_01 0x48

extern const char* I2C_DEV;
extern int i2c_fd;
extern const int adcChannel;
extern int brightness;
extern pthread_mutex_t lock_brightness;

void light_init();
int getBrightness();

#endif