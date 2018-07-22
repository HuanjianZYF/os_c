//
//  pipe2.c
//  os_c
//
//  Created by mac_zyf on 2018/7/21.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "pipe.h"

int main() {
    FILE *file1, *file2;
    char *buffer;
    
    buffer = malloc(sizeof(char) * 200);
    //以读的方式打开一个管道
    file1 = popen("ls -al /", "r");
    while (fread(buffer, 200, 1, file1) > 0) {
        printf("%s\n", buffer);
    }
    pclose(file1);
    
    //以写的方式打开一个管道
    file2 = popen("grep -a zyf", "w");
    fwrite("aaaaaa\nzyf skjs\ndishdid\ncgdzyf\ngsdfcdf\n", 1000, 1, file2);
    
    pclose(file2);
    free(buffer);
    return 1;
}

