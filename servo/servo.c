

// servo
#define SERVO 18
#define RANGE 2000 // 서보모터는 50hz에서 동작. 이에 따른 범위와 클럭 지정
#define CLOCK 192
#define MAX 246 // duty값 범위.
#define MEAN 150
#define MIN 54
#define SERVO_ON 200
#define SERVO_OFF 100

// servo
void init_servo()
{
    pinMode(SERVO, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(RANGE);
    pwmSetClock(CLOCK);
    pwmWrite(SERVO, MEAN);
    delay(10);
}

void *onSwitch()
{
    pwmWrite(SERVO, SERVO_ON);
    delay(500);
    return NULL;
}

void *offSwitch()
{
    pwmWrite(SERVO, SERVO_OFF);
    delay(500);
    return NULL;
}
