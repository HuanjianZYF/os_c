//
//  file_io.c
//  os_c
//
//  Created by mac_zyf on 2018/7/2.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "file_io.h"
#define BUFFER_SIZE 100

int main() {
    int fd1, fd2; //文件描述符
    char* fileName1 = "/Users/zyf/Documents/a.json"; //要打开的文件名
    char* fileName2 = "/Users/zyf/Documents/zzz.txt"; //要创建的文件名
    off_t offset; //偏移量
    char buffer[BUFFER_SIZE]; //缓冲
    char writeBuffer[10] = "abcdefghi"; //写缓冲
    
    
    fd1 = open(fileName1, O_RDWR|O_APPEND); //读写，追加
    fd2 = open(fileName2, O_RDONLY|O_CREAT|O_TRUNC, 0); //创建文件，权限暂时不知道怎么赋值
    offset = lseek(fd1, 0, SEEK_CUR); //获得当前文件偏移量,如果是管道，网络套接字会返回-1
    printf("%lld\n", offset);
    
    if (read(fd1, buffer, BUFFER_SIZE) < 0) { //读100个字节到缓冲区
        errorSay("文件读错了");
    }
    printf("%s\n", buffer);
    
    offset = lseek(fd1, 0, SEEK_CUR); //再看看offset
    printf("%lld\n", offset);
    
    if (write(fd1, writeBuffer, 10) < 0) {
        errorSay("文件写出问题了");
    }
    
    errorSay("哈哈哈"); //测试头文件
    close(fd1);
    close(fd2);
}

