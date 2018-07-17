//
//  daemon.c
//  os_c
//
//  让自己成为一个守护进程是一个变态的行为。
//  Created by mac_zyf on 2018/7/17.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "daemon.h"

int main() {
    pid_t pid;
    int i, fd0, fd1, fd2;
    struct rlimit limit; //文件描述符
    
    //创建一个子进程，且让父进程退出，这样子进程就不会是组长，父进程退出还会让这个子进程和别人毫无关联。
    if ((pid = fork()) != 0) {
        exit(0);
    }
    
    //建一个自己的会话，一般一个守护进程自己是一个会话，自己是一个组，组合会话里就只有自己。
    setsid();
    
    //关闭所有的文件描述符
    getrlimit(RLIMIT_NOFILE, &limit);
    if (limit.rlim_max == RLIM_INFINITY) {
        limit.rlim_max = 1024;
    }
    for (i = 0; i < limit.rlim_max; i++) {
        close(i);
    }
    
    //让文件描述符0，1，2都指向/dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0); //dup会复制一个文件描述符，指向同一个文件描述符表表项。
    fd2 = dup(0);
    
    //切换工作目录到根目录
    chdir("/");
    //设置文件权限屏蔽字，组和其他不能写
    umask(S_IWGRP|S_IWOTH);
    
    openlog("zyf..", LOG_CONS, LOG_NOTICE);
    syslog(LOG_NOTICE, "通知你下");
    sleep(1000);
}
