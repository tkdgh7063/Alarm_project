#include <stdio.h>
#include <wiringPi.h>

#define SDI 0   // Serial Data Input
#define RCLK 1  // memory clock input(STCP)
#define SRCLK 2 // shift register clock input(SHCP)

unsigned char SegCode[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void fnd_init() {
    pinMode(SDI, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);

    digitalWrite(SDI, LOW);
	digitalWrite(RCLK, LOW);
	digitalWrite(SRCLK, LOW);
}

void hc595_shift(unsigned char dat){
	int i;

	for(i=0;i<8;i++){
		digitalWrite(SDI, 0x80 & (dat << i));
		digitalWrite(SRCLK, 1);
		delay(1);
		digitalWrite(SRCLK, 0);
	}

		digitalWrite(RCLK, 1);
		delay(1);
		digitalWrite(RCLK, 0);
}

int main(void){
	int i;

	if(wiringPiSetup() == -1){ //when initialize wiring failed, print messageto screen
		printf("setup wiringPi failed !");
		return 1;
	}

	fnd_init();
	while(1){
		for(i=0;i<10;i++){
			printf("Print %1X on Segment\n", i); // %X means hex output
			hc595_shift(SegCode[i]);
			delay(500);
		}
	}

	return 0;
}