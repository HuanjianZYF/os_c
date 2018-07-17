//
//  thread_property.c
//  os_c
//
//  Created by mac_zyf on 2018/7/16.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "thread_property.h"
void init_thread_attr(pthread_attr_t *t);
void *f(void *param);

int main() {
    pthread_attr_t thread_attr; //线程属性
    pthread_t pid;
    
    init_thread_attr(&thread_attr); //设置线程属性
    pthread_create(&pid, &thread_attr, f, NULL); //这个线程拥有了我赋予的属性
    pthread_attr_destroy(&thread_attr); //收尸
}

void init_thread_attr(pthread_attr_t *t) {
    pthread_attr_init(t);
    pthread_attr_setdetachstate(t, PTHREAD_CREATE_DETACHED); //以分离状态创建线程
    //别的还有栈属性啥的就不来设置了。
}

void *f(void *param) {
    printf("heh\n");
    return (void*) 0;
}
