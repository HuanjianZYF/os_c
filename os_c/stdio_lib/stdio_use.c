//
//  stdio_use.c
//  os_c
//
//  Created by mac_zyf on 2018/7/4.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "stdio_use.h"
#define BUFFER_SIZE 20

int main() {
    FILE *file1; //文件指针
    int character;
    char buffer[BUFFER_SIZE];
    long cursor; //游标
    char *p = buffer;
    
    file1 = fopen("/Users/zyf/Documents/a.json", "a+"); //得到一个文件流,读写追加
    
    //从标准输入流中拿到一个字符，写到刚才那个文件
    character = getc(stdin);
    putc(character, file1);
    fflush(file1);
    
    //从文件读出一行或者BUFFER_SIZE个数据
    rewind(file1); //从写入一个流转换姿态变成读出
    fgets(buffer, 19, file1);
    buffer[19] = '\0';
    printf("%s\n", buffer);
    
    //再往文件写一堆数据
    rewind(file1);
    fputs("\n听懂别人的说话很难啊", file1);
    fflush(file1);
    
    //试试seek
    cursor = ftell(file1);
    printf("%ld\n", cursor);
    fseek(file1, cursor - 10, SEEK_SET);
    cursor = ftell(file1);
    printf("%ld\n", cursor);
    
    //当然也可以这样
    fprintf(file1, "\n其实并不难，两个人的事情，两人分担");
    
    //再试试scanf,主要用于格式化输入
    fscanf(file1, "%s", p);
    printf("%s", p);
    
    fclose(file1); //关闭文件
}
