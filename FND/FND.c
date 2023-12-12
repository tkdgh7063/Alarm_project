#include <stdio.h>
#include <wiringPi.h>

// FND의 각 세그먼트에 대한 GPIO 핀 설정
#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6
#define SEG_DP 7

// FND의 자릿수에 대한 GPIO 핀 설정
#define DIGIT_1 21
#define DIGIT_2 22
#define DIGIT_3 23
#define DIGIT_4 24

// 각 숫자에 대한 7세그먼트 표시 값
const int SEGMENTS[10] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111  // 9
};

void FND_init() {
    // 세그먼트 핀 초기화
    pinMode(SEG_A, OUTPUT);
    pinMode(SEG_B, OUTPUT);
    pinMode(SEG_C, OUTPUT);
    pinMode(SEG_D, OUTPUT);
    pinMode(SEG_E, OUTPUT);
    pinMode(SEG_F, OUTPUT);
    pinMode(SEG_G, OUTPUT);
    pinMode(SEG_DP, OUTPUT);

    // 자릿수 핀 초기화
    pinMode(DIGIT_1, OUTPUT);
    pinMode(DIGIT_2, OUTPUT);
    pinMode(DIGIT_3, OUTPUT);
    pinMode(DIGIT_4, OUTPUT);
}

void displayTime(int hour, int min) {
    int digit1 = hour / 10;
    int digit2 = hour % 10;
    int digit3 = min / 10;
    int digit4 = min % 10;

    digitalWrite(DIGIT_1, HIGH);
    digitalWrite(DIGIT_2, LOW);
    digitalWrite(DIGIT_3, LOW);
    digitalWrite(DIGIT_4, LOW);
    displayDigit(SEGMENTS[digit1]);

    digitalWrite(DIGIT_1, LOW);
    digitalWrite(DIGIT_2, HIGH);
    digitalWrite(DIGIT_3, LOW);
    digitalWrite(DIGIT_4, LOW);
    displayDigit(SEGMENTS[digit2]);

    digitalWrite(DIGIT_1, LOW);
    digitalWrite(DIGIT_2, LOW);
    digitalWrite(DIGIT_3, HIGH);
    digitalWrite(DIGIT_4, LOW);
    displayDigit(SEGMENTS[digit3]);

    digitalWrite(DIGIT_1, LOW);
    digitalWrite(DIGIT_2, LOW);
    digitalWrite(DIGIT_3, LOW);
    digitalWrite(DIGIT_4, HIGH);
    displayDigit(SEGMENTS[digit4]);
}

void displayNum(int num) {
    int digit1 = num / 1000;
    int digit2 = num % 1000 / 100;
    int digit3 = num % 100 / 10;
    int digit4 = num % 10;

    digitalWrite(DIGIT_1, HIGH);
    digitalWrite(DIGIT_2, LOW);
    digitalWrite(DIGIT_3, LOW);
    digitalWrite(DIGIT_4, LOW);
    displayDigit(SEGMENTS[digit1]);

    digitalWrite(DIGIT_1, LOW);
    digitalWrite(DIGIT_2, HIGH);
    digitalWrite(DIGIT_3, LOW);
    digitalWrite(DIGIT_4, LOW);
    displayDigit(SEGMENTS[digit2]);

    digitalWrite(DIGIT_1, LOW);
    digitalWrite(DIGIT_2, LOW);
    digitalWrite(DIGIT_3, HIGH);
    digitalWrite(DIGIT_4, LOW);
    displayDigit(SEGMENTS[digit3]);

    digitalWrite(DIGIT_1, LOW);
    digitalWrite(DIGIT_2, LOW);
    digitalWrite(DIGIT_3, LOW);
    digitalWrite(DIGIT_4, HIGH);
    displayDigit(SEGMENTS[digit4]);
}

void displayDigit(int segments) {
    // 각 세그먼트에 대한 값을 설정하여 FND에 표시
    digitalWrite(SEG_A, (segments & 0x01) >> 0);
    digitalWrite(SEG_B, (segments & 0x02) >> 1);
    digitalWrite(SEG_C, (segments & 0x04) >> 2);
    digitalWrite(SEG_D, (segments & 0x08) >> 3);
    digitalWrite(SEG_E, (segments & 0x10) >> 4);
    digitalWrite(SEG_F, (segments & 0x20) >> 5);
    digitalWrite(SEG_G, (segments & 0x40) >> 6);
    digitalWrite(SEG_DP, (segments & 0x80) >> 7);
}