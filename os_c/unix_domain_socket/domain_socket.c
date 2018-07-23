//
//  domain_socket.c
//  os_c
//
//  Created by mac_zyf on 2018/7/23.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "domain_socket.h"
#define BUFFER_SIZE 100

int main() {
    int fd_socket[2]; //两个套接字描述符
    char buffer[BUFFER_SIZE];
    pid_t pid;
    
    //UNIX域套接字类似于双向管道，用socketpair创建两个没有名字的域套接字
    socketpair(AF_UNIX, SOCK_STREAM, 0, fd_socket); //打开两个描述符
    if ((pid = fork()) <= 0) {
        write(fd_socket[0], "hello\n", 6);
        sleep(1);
        read(fd_socket[1], buffer, 7);
        printf("%s\n", buffer);
    } else {
        read(fd_socket[1], buffer, 6);
        write(fd_socket[0], "hello2\n", 7);
        printf("%s\n", buffer);
        waitpid(pid, (void*) 0, 0);
    }
    
}
