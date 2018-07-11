//
//  terminal_process_group.c
//  os_c
//
//  Created by mac_zyf on 2018/7/9.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "terminal_process_group.h"

int main() {
    pid_t pid;
    
    printf("当前进程id%d;当前进程组id%d;当前会话id%d\n", getpid(), getpgrp(),getsid(getpid()));
    setsid(); //设置会话
    printf("当前进程id%d;当前进程组id%d;当前会话id%d\n", getpid(), getpgrp(),getsid(getpid()));

    if ((pid = fork()) == 0) { //在子进程中
        setpgid(0, getppid());
        printf("子进程中 当前进程id%d;当前进程组id%d;当前会话id%d\n", getpid(), getpgrp(),getsid(getpid()));
        _exit(0);
    } else {
        setpgid(pid, getpid()); //在父进程中和子进程中都设置子进程的进程组id
    }
    
    
}
