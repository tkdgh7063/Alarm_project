#include "music.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

pid_t music(int stat){
    pid_t pid = fork();
    if(pid>0){
        return pid;
    }
    else if(pid == 0){
        char buf[1024];
        int r = rand() % 2;
        sprintf(buf,"%d",r);        
        char* cmd[] = {"tone", buf, NULL};
        execv(cmd[0], cmd);
    }
    else{
        printf("[music] fork error...\n");
    }
}
