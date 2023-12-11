#include "music.h"
#include <stdio.h>

pid_t music(int stat){
    pid_t pid = fork();
    if(pid>0){
        return pid;
    }
    else if(pid == 0){
        char buf[1024];
        sprintf(buf,"%d",stat);
        char* cmd[] = {"speaker", buf, NULL};
        execv(cmd[0], cmd);
    }
    else{
        printf("[music] fork error...\n");
    }
}
