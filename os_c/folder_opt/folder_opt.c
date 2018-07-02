//
//  folder_opt.c
//  os_c
//
//  Created by mac_zyf on 2018/7/2.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "folder_opt.h"
char* getFileType(char* folderName); //获取文件类型

int main() {
    char* fileType;
    
    fileType = getFileType("/dev/tty");
    printf("%s\n", fileType);
}

char* getFileType(char* folderName) {
    struct stat buffer;
    mode_t mode;
    
    if (stat(folderName, &buffer) < 0) {
        errorSay("读文件状态不对");
        return "未知类型";
    }
    
    mode = buffer.st_mode;
    if (S_ISREG(mode)) {
        return "普通文件";
    } else if (S_ISDIR(mode)) {
        return "目录文件";
    } else if (S_ISCHR(mode)) {
        return "字符设备特殊文件";
    } else if (S_ISBLK(mode)) {
        return "块设备特殊文件";
    } else if (S_ISFIFO(mode)) {
        return "FIFO文件";
    } else if (S_ISLNK(mode)) {
        return "链接文件";
    } else if (S_ISSOCK(mode)) {
        return "socket文件";
    } else {
        return "未知类型";
    }
}
