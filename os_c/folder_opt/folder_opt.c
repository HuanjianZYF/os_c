//
//  folder_opt.c
//  os_c
//  练习用
//
//  Created by mac_zyf on 2018/7/2.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "folder_opt.h"
char* getFileType(char* folderName); //获取文件类型
long getFileSize(char* folderName); //获取文件大小
void getPermissionStr(char* folderName, char* result); //获取文件权限字符串
int isPermissionBitSet(mode_t mode, mode_t bit); //判断某一个权限位是否被设置

int main() {
    char block[10]; //暂时忘记malloc了..囧
    char *fileType, *permissionStr = block;
    long fileSize;
    int fd;
    struct stat buffer;
    mode_t mode;
    
    fileType = getFileType("/dev/tty");
    fileSize = getFileSize("/Users/zyf/Documents/url修改.numbers");
    
    umask(S_IWOTH|S_IWGRP|S_IXGRP|S_IXOTH); //想要创建一个文件，组和其他没有写和执行权限
    fd = open("/Users/zyf/Documents/test",
              O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IROTH|S_IWOTH); //创建文件
    
    if (fstat(fd, &buffer) < 0) { //拿到文件状态
        errorSay("读文件状态不对");
    }
    mode = buffer.st_mode;
    
    fchmod(fd, (mode & ~S_IWUSR) | S_IWGRP); //修改文件权限本人不能写，组能执行
    getPermissionStr("/Users/zyf/Documents/test", permissionStr); //拿到该文件的权限字符串
    
    unlink("/Users/zyf/Documents/test"); //取消该文件的连接
    printf("该文件类型：%s\n文件大小：%ld\n文件权限：%s\n", fileType, fileSize, permissionStr);
}

char* getFileType(char* folderName) {
    struct stat buffer;
    mode_t mode;
    
    if (lstat(folderName, &buffer) < 0) {
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

long getFileSize(char* folderName) {
    struct stat buffer;
    
    if (lstat(folderName, &buffer) < 0) {
        errorSay("读文件状态不对");
        return 0;
    }
    return buffer.st_size;
}

void getPermissionStr(char* folderName, char* result) {
    struct stat buffer;
    mode_t mode;
    mode_t modeArr[9] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    int i;
    int mod; //余数
    
    if (lstat(folderName, &buffer) < 0) {
        errorSay("读文件状态不对");
        return;
    }
    
    mode = buffer.st_mode;
    for (i = 0; i < 9; i++) {
        if (isPermissionBitSet(mode, modeArr[i])) {
            mod = i % 3;
            if (mod == 0) {
                *result = 'r';
            } else if (mod == 1) {
                *result = 'w';
            } else {
                *result = 'x';
            }
        } else {
            *result = '_';
        }
        result++;
    }
    result[i] = '\0';
}

int isPermissionBitSet(mode_t mode, mode_t bit) {
    if (mode == (mode | bit)) {
        return 1;
    }
    return 0;
}
