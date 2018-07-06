//
//  process_test1.c
//  os_c
//
//  Created by mac_zyf on 2018/7/6.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "process_test1.h"
int jmpPos; //返回点,全局变量

void myexit1(void);
void myexit2(void);
void f(void);

int main(int argc, char *argv[]) {
    int i;
    char *ptr;
    int jmpRet; //跳转返回值
    
    //打印参数
    for (i = 0; i < argc; i++) {
        printf("argv[%d]:%s\n",i , argv[i]);
    }
    
    //关联了函数给退出函数，使进程调用exit时，会先执行这几个函数
    atexit(myexit1);
    atexit(myexit2);
    atexit(myexit2);
    
    //获得环境变量
    printf("%s\n", getenv("PATH"));
    
    //会用malloc了，原来在stdlib.h里面啊
    ptr = malloc(sizeof(char) * 10);
    for (i = 0; i < 9; i++) {
        *(ptr + i) = 'a' + i;
    }
    *(ptr + 9) = '\0';
    printf("%s\n", ptr);
    free(ptr); //貌似要记得free
    
    //calloc也是一样的
    ptr = calloc(sizeof(char), 10);
    for (i = 0; i < 9; i++) {
        *(ptr + i) = 'a' + i + 1;
    }
    *(ptr + 9) = '\0';
    printf("%s\n", ptr);
    free(ptr);
    
    //设置一个返回点,就像try catch一样
    if ((jmpRet = setjmp(&jmpPos)) != 0) {
        switch (jmpRet) {
            case 1:
                printf("1错误\n");
                exit(1);
                break;
            case 2:
                printf("2错误\n");
                exit(2);
                break;
            default:
                printf("default\n");
                break;
        }
    }
    
    //飞一下
    f();
    
    return 0;
}

void myexit1(void) {
    printf("1\n");
}

void myexit2(void) {
    printf("2\n");
}

void f(void) {
    longjmp(&jmpPos, 2);
}
