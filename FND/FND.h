#ifndef FND_H
#define FND_H

#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6
#define SEG_DP 7

#define DIGIT_1 21
#define DIGIT_2 22
#define DIGIT_3 23
#define DIGIT_4 24

extern const int SEGMENTS[10];

void FND_init();
void displayTime(int hour, int min);
void displayNum(int num);
void displayDigit(int segments);

#endif /* FND_H */
