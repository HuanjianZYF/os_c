//
//  file_io.h
//  os_c
//
//  Created by mac_zyf on 2018/7/2.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#ifndef file_io_h
#define file_io_h

#include <stdio.h>
#include <unistd.h> //定义了标准输入，标准输出，标准错误的常量定义
#include <fcntl.h> //定义了文件控制的一些函数

void errorSay(char* s);

void errorSay(char* s) {
    printf("%s\n", s);
}

#endif /* file_io_h */
