//
//  mysignal2.c
//  os_c
//
//  Created by mac_zyf on 2018/7/13.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "mysignal.h"
void alrm_deal(int signo);
void zyf(void);
int jmp;

int main2() {
    if (signal(SIGALRM, alrm_deal) == SIG_ERR) {
        printf("注册信号处理函数错误\n");
    }
    
    //无论发生了什么，5秒之后就能出来
    if (setjmp(&jmp) == 0) {
        alarm(5);
        zyf();//一个永远
    }
    printf("5秒钟我就出来了\n");
    return 1;
}

void alrm_deal(int signo) {
    longjmp(&jmp, 1);
}

void zyf() {
    int i;
    for (i = 0; i < 9999999; i++) {
        sleep(100);
    }
}
