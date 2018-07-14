//
//  mysignal4.c
//  os_c
//
//  Created by mac_zyf on 2018/7/14.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "mysignal.h"
void sigdeal(int signo);

int main() {
    struct sigaction act, oact;
    sigset_t sigset;
    char *a;
    
    //试一下用sigaction
    act.sa_handler = sigdeal;
    
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1); //中断处理函数中屏蔽SIGUSR1
    act.sa_mask = sigset;
    act.sa_flags = 0;
    sigaction(SIGUSR1, &act, &oact);
    
    //打印信号名字
    a = malloc(sizeof(char) * 20);
    psignal(SIGUSR1, a);
    printf("%s\n", a);
    free(a);
    sleep(100);
}

void sigdeal(int signo) {
    printf("信号处理函数\n");
    sleep(20);
}
