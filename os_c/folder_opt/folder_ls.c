//
//  folder_ls.c
//  os_c
//  递归打印目录下的所有文件
//
//  Created by mac_zyf on 2018/7/4.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "folder_opt.h"
void printFolder(char* folderName, int level); //打印该目录下一层的所有目录，如果是文件则return

int main() {
    char a[100];
    char *p = a;
    printFolder("/Users/zyf/Documents", 0);
    
    chdir("/Users/zyf/Documents");
    getcwd(p, 100); //打印出当前路径
    printf("%s\n", p);
}

void printFolder(char* folderName, int level) {
    struct stat fileStat; //文件状态
    char a[1000]; //不会用malloc...
    char* p = a;
    mode_t mode;
    DIR * dir;
    struct dirent *dirent;
    int i;
    
    if (lstat(folderName, &fileStat) < -1) {
        errorSay("获取文件状态出错");
        return;
    }
    
    mode = fileStat.st_mode;
    if ((mode | S_IFDIR) != mode) { //不是目录
        return;
    }
    
    dir = opendir(folderName);
    while ((dirent = readdir(dir)) != NULL) {
        if (strcmp(".", dirent->d_name) != 0 && strcmp("..", dirent->d_name)) { //不用打印.和..
            for (i = 0; i < level; i++) {
                printf("---*");
            }
            printf("%s\n", dirent->d_name);
            strcpy(p, folderName); //睿智的操作
            strcat(p, "/");
            strcat(p, dirent->d_name);
            printFolder(p, level + 1);
        }
    }
}
