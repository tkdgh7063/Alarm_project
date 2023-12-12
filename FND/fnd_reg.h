#ifndef FND_REG_H
#define FND_REG_H

#define SDI 0   // Serial Data Input
#define RCLK 1  // Memory clock input(STCP)
#define SRCLK 2 // Shift register clock input(SHCP)

extern const int placePin[4];
extern unsigned char SegCode[10];

void fnd_init();
void pickDigit(int digit);
void clearDisplay();
void hc595_shift(unsigned char dat);
void displayTime(int hour, int min);
void displayNum(int num);

#endif /* FND_REG_H */
