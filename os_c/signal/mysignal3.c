//
//  mysignal3.c
//  os_c
//
//  Created by mac_zyf on 2018/7/13.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "mysignal.h"
void sigdeal(int signo);

int main3() {
    sigset_t sigset;
    sigset_t blockset; //阻塞信号集合
    
    if (signal(SIGUSR1, sigdeal) == SIG_ERR) {
        printf("注册信号处理函数出错");
    }
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL); //添加到阻塞集合中
    sleep(10);
    sigpending(&blockset);
    if (sigismember(&blockset, SIGUSR1)) {
        printf("USR1信号已经被阻塞\n");
    }
    sleep(10);
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);//解除阻塞
    
    return 1;
}

void sigdeal(int signo) {
    printf("进来了SIGUSR1信号的处理函数\n");
    signal(SIGUSR1, SIG_DFL); //弄回去
}
