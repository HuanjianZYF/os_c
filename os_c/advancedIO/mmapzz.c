//
//  mmapzz.c
//  os_c
//
//  Created by mac_zyf on 2018/7/19.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "mmapzz.h"

int main() {
    int fd;
    void *memery_start; //映射的内存起始地址
    struct stat file_stat; //文件状态
    char* p;
    
    fd = open("/Users/zyf/Documents/a.json", O_RDWR); //打开一个文件
    fstat(fd, &file_stat); //得到文件状态，想要知道这个文件多大
    
    //进行文件内存映射，返回映射后的内存地址
    memery_start = mmap(0, file_stat.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    p = (char *) memery_start;
    
    printf("%s\n", p);
    
    *(p + 3) = '$'; //将第四个字符替换为$,在内存中替换，在程序退出后会同步到文件
    return 1;
}
