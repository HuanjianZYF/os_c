//
//  signal.c
//  os_c
//
//  Created by mac_zyf on 2018/7/12.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "mysignal.h"

void sigdeal(int signo);
void alarmdeal(int signo);

int main1() {
    struct passwd *ptr;

    //注册SIGUSR1和SIGUSR2的信号处理函数
    if (signal(SIGUSR1, sigdeal) == SIG_ERR) {
        printf("信号处理函数不行\n");
    }
    if (signal(SIGUSR2, sigdeal) == SIG_ERR) {
        printf("信号处理函数不行\n");
    }
    if (signal(SIGSEGV, sigdeal) == SIG_ERR) {
        printf("信号处理函数不行\n");
    }

    //注册闹钟信号处理函数，测试可重入函数
    if (signal(SIGALRM, alarmdeal) == SIG_ERR) {
        printf("信号处理函数不行\n");
    }
    alarm(1);

    while(1) {
        if ((ptr = getpwnam("zyf")) == NULL) {
            printf("主程序中读的不对\n");
        }
        if (strcmp(ptr->pw_name, "zyf") != 0) { //这是不可能的吧,毕竟信号处理区别于并行
            printf("怎么读的不一样呢\n");
        }
    }
    return 1;
}

//信号处理函数，接到信号打印信号
void sigdeal(int signo) {
    printf("%d\n", signo);
}

//在信号处理函数中调用getpwnam这个函数是不可重入的
//不加getpwnam时会滴答滴答滴答...加了就只有滴答...程序出错了。
void alarmdeal(int signo) {
    struct passwd *pwd;

    printf("滴答\n");

    if ((pwd = getpwnam("root")) == NULL) {
        printf("信号处理函数中读的不对\n");
    }
    alarm(1);
}

