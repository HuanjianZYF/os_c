//
//  pthread_use2.c
//  os_c
//
//  Created by mac_zyf on 2018/7/15.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "pthread_use.h"
void *thread1(void *param);
void *thread2(void *param);

int main() {
    pthread_t pid1, pid2;
    int ret;
    void *a;
    
    ret = pthread_create(&pid1, NULL, thread1, NULL);
    if (ret != 0) {
        printf("新建线程出错\n");
    }
    
    ret = pthread_create(&pid2, NULL, thread2, NULL);
    if (ret != 0) {
        printf("新建线程出错\n");
    }
    
    //join可以等待一个线程完成，并拿到它的返回结果
    pthread_join(pid1, &a);
    printf("等待线程1完成，并拿到了线程1的返回结果%d\n",  (int) a);
}

void *thread1(void *param) {
    printf("thread1 runing\n");
    sleep(10);
    pthread_exit((void*) 98);
}

void *thread2(void *param) {
    printf("thread2 runing\n");
    sleep(5);
    pthread_exit((void*) 0);
}
