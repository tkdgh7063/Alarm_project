#include <stdio.h>
#include <wiringPi.h>

#define SDI 0   // Serial Data Input
#define RCLK 1  // memory clock input(STCP)
#define SRCLK 2 // shift register clock input(SHCP)

const int placePin[] = {12, 3, 2, 0};
unsigned char SegCode[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void fnd_init() {
    pinMode(SDI, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);

    digitalWrite(SDI, LOW);
	digitalWrite(RCLK, LOW);
	digitalWrite(SRCLK, LOW);
}

void pickDigit(int digit) {
    int i;
    for (i=0; i<4; i++) {
        digitalWrite(placePin[i], LOW);
    }
    digitalWrite(placePin[digit], HIGH);
}

void clearDisplay() {
    int i;
    for (i = 0; i < 8; i++)
    {
        digitalWrite(SDI, 1);
        digitalWrite(SRCLK, 1);
        delayMicroseconds(1);
        digitalWrite(SRCLK, 0);
    }
    digitalWrite(RCLK, 1);
    delayMicroseconds(1);
    digitalWrite(RCLK, 0);
}

void hc595_shift(unsigned char dat) {
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

void display(int hour, int min) {
    int digits[] = [hour/10, hour%10, min/10, min%10];
    // int digit1 = hour / 10;
    // int digit2 = hour % 10;
    // int digit3 = min / 10;
    // int digit4 = min % 10;

    int i;
    for (i=0; i<4; i++) {
        clearDisplay();
        pickDigit(i);
        hc595_shift(digits[i]);
    }
}

void displayDigit(int segments) {

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
