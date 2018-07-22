//
//  pipe.c
//  os_c
//
//  Created by mac_zyf on 2018/7/19.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "pipe.h"

int main() {
    int fd[2];
    char buffer[40];
    pid_t pid;
    
    //生成一个管道，从fd[0]读到fd[1]的数据
    pipe(fd);
    
    write(fd[1], "hello\n", 6);
    read(fd[0], buffer, 6);
    write(STDOUT_FILENO, buffer, 6);
    printf("管道打开了两个描述符%d %d\n", fd[0], fd[1]);
    
    //一个管道其实就是打开了两个文件描述符，一个文件描述符的写入会在另一个描述符能读出来。
    //一般先弄一个管道，再fork，让进程间通过这个文件描述符通信
    pipe(fd);
    printf("管道又打开了两个描述符%d %d\n", fd[0], fd[1]);
    if ((pid = fork()) > 0 ) {
        close(fd[1]);
        read(fd[0], buffer, 40);
        write(STDOUT_FILENO, buffer, 40);
    } else {
        close(fd[0]);
        sleep(10);
        write(fd[1], "I am father process, can ..\n", 40);
    }
}
