//
//  process_test2.c
//  os_c
//
//  Created by mac_zyf on 2018/7/7.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "process_test2.h"

int main() {
    int pid;
    char *a[3];
    
    //打印出进程id，父进程id，实际uid，有效uid，实际组id，有效组id
    printf("pid：%d ppid：%d\nuid：%d euid：%d\ngid：%d egid：%d\n",
           getpid(), getppid(), getuid(), geteuid(), getgid(), getegid());
    
    //fork一个进程
    if ((pid = fork()) == 0) { //在子进程
        printf("子进程,pid是%d\n", getpid());
        _exit(0);
    } else {
        waitpid(pid, NULL, 0); //等待子进程执行完
        printf("父进程,创建的子进程pid是%d\n", pid);
    }
    printf("父进程和子进程都有\n");
    
    //用exec
    if ((pid = fork()) == 0) {
        a[0] = ""; //组装echo的参数
        a[1] = "hello";
        a[2] = NULL;
        if (execvp("echo", a) < 0) { //执行echo这个可执行文件
            printf("执行不了\n");
        }
        _exit(0);
    } else {
        waitpid(pid, NULL, 0);
    }
    
    //system函数,这个可以在c代码里面写命令，其实是连续调用了fork,exec,waitpid
    system("ls -al /");
    
    //登录用户名
    printf("%s\n", getlogin());
    
    
}
