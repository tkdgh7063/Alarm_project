#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdbool.h>

#include "keypad.h"

#define SCL 21
#define SDA 20

bool _GetBit()
{
	digitalWrite(SCL, LOW);
	delayMicroseconds(2); // 500KHz
	bool retVal = !digitalRead(SDA);
	digitalWrite(SCL, HIGH);
	delayMicroseconds(2); // 500KHz
	return retVal;
}

void init_keypad(){
    if (wiringPiSetupGpio() == -1)
        return;
    pinMode(SCL, OUTPUT);
    pinMode(SDA, INPUT);
    digitalWrite(SCL, HIGH);
    printf("keypad set\n");
}

unsigned char getSingleKey(){
    unsigned char result = 0;
    printf("start get key\n");
    while (1)
    {
        //입력이 들어올 때 까지 대기
        while (digitalRead(SDA)); // DV LOW
	    while (!digitalRead(SDA)); // DV HIGH
	    delayMicroseconds(10);
        printf("touched\n");
        //몇 번 숫자가 눌렸는지 체크
        result = 0;
	    for (unsigned char i = 0; i < 8; i++){
            if (_GetBit()) {
                result = i + 1;
                }
        }
	    delay(2); // Tout
        break;
        // if(result != 0){
        //     printf("in kepad.c %d\n", result);
        //     delay(1000);
        // }
    }
    return result;
}
