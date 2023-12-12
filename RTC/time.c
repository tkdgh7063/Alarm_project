#include "RTC.h"
#include "../FND/fnd_reg.h"

// RTC main
void main() {
    // 시간 출력
    // fork()

    // RTC_init();
    // FND_init();
    
    int hour;
    int min;
    
    while (1) {
        hour = getHour();
        min = getMin();

        display(hour, min);
        
        delay(100); // 0.1초 대기
    }

    return 0;
}