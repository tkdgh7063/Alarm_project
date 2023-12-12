#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <spawn.h>

#include "FND/fnd_reg.h"
#include "FND/FND.h"
#include "illumination/light.h"
#include "RTC/RTC.h"
#include "speaker/music.h"
#include "KEYPAD/keypad.h"

void main(){
    init_keypad();
    unsigned char result;
    while (1)
    {
        result=0;
        result=getSingleKey();
        if(result != 0){
            printf("result = %d\n", result);
        }
        delay(1000);
    }
    
    
    
}