//
//  pthread_use3.c
//  os_c
//
//  Created by mac_zyf on 2018/7/16.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "pthread_use.h"
typedef struct {
    int variable;  //同步变量
    pthread_mutex_t lock; //锁变量
} lock_struct;

void add(int i, lock_struct *lock); //给同步变量增加i
void * thread1(void * param);

int main() {
    lock_struct lock;
    pthread_t pid1, pid2, pid3;
    
    lock.variable = 0; //初始化初始值为0
    pthread_mutex_init(&(lock.lock), NULL); //初始化锁变量
    
    pthread_create(&pid1, NULL, thread1, &lock); //新建一个线程
    pthread_create(&pid2, NULL, thread1, &lock);
    pthread_create(&pid3, NULL, thread1, &lock);
    add(100, &lock);
    
    //等三个线程执行完
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    pthread_join(pid3, NULL);
    printf("%d\n", lock.variable); //预计输出30100，如果不加锁，那么输出的就很小了
    
    pthread_mutex_destroy(&(lock.lock)); //摧毁锁
    return 1;
}

//原子操作
void add(int i, lock_struct *lock) {
    pthread_mutex_lock(&(lock->lock));
    lock->variable += i;
    pthread_mutex_unlock(&(lock->lock));
}

void * thread1(void *param) {
    int i;

    param = (lock_struct *) param;
    for (i = 0; i < 10000; i++) {
        add(1, param);
    }
    
    return (void*) 0;
}
