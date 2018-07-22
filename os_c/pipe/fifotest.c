//
//  fifotest.c
//  os_c
//
//  Created by mac_zyf on 2018/7/22.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "pipe.h"

//fifo表现形式是一个文件，可是它类似于一个管道，可以有一个进程读取fifo的数据
//然后另外一些进程对fifo文件进行写，这样可以不需要一个临时文件就能完成进程间通信

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("参数两个\n");
        return 1;
    }
    
    //输入什么打印什么
    printf("%s", *(argv + 1));
}
