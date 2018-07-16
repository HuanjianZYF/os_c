//
//  pthread_use.c
//  os_c
//
//  Created by mac_zyf on 2018/7/15.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "pthread_use.h"
void *thread1(void *param);
void *thread2(void *param);

int main() {
    pthread_t pid1, pid2; //线程id
    int ret1, ret2;
    
    ret1 = pthread_create(&pid1, NULL, thread1, NULL); //新建一个线程1
    if (ret1 != 0) {
        printf("新建线程出错\n");
    }
    printf("进程id:%d;线程id:%ld\n", getpid(), (long) pid1);
    
    ret2 = pthread_create(&pid2, NULL, thread2, NULL); //新建一个线程2
    if (ret2 != 0) {
        printf("新建线程出错\n");
    }
    printf("进程id:%d;线程id:%ld\n", getpid(), (long) pid2);

    sleep(100); //主线程退出则别的线程也会退出
}

void *thread1(void *param) { //这个返回值并不是pthread_create的ret
    printf("线程1执行pid:%ld\n", (long) pthread_self());
    sleep(5);
    printf("线程1执行结束\n");
    return (void *) 0;
}

void *thread2(void *param) {
    printf("线程2执行pid:%ld\n", (long) pthread_self());
    sleep(5);
    printf("线程2执行结束\n");
    return (void *) 0;
}
