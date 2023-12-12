// 알람 울리는 코드

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

#include "../FND/fnd_reg.h"
#include "../speaker/music.h"
// 터치패드 파일

int main() {
    pid_t pid = music();

    srand(time(NULL));

    int randomNum = rand() % 9000 + 1000;
    displayNum(randomNum);

    int i;
    while (1) {
        // 터치패드 입력 받기
        if (i == randomNum) {
            break;
        }
        else {
            continue;
        }
    }

    if (kill(pid, SIGTERM) != 0) {
        printf("MUSIC 프로세스 종료 실패\n");
        return 1;
    }

    return 0;
}