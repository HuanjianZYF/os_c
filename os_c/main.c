//
//  main.c
//  os_c
//
//  Created by mac_zyf on 2018/7/2.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char * a;
    
    a = strerror(34);
    printf("Hello, World!\n%s\n", a);
    perror(a);
    return 0;
}
