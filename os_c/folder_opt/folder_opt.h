//
//  folder_opt.h
//  os_c
//
//  Created by mac_zyf on 2018/7/2.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#ifndef folder_opt_h
#define folder_opt_h

#include <stdio.h>
#include <sys/stat.h>
#include <sys/termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

void errorSay(char* s);

void errorSay(char* s) {
    printf("%s\n", s);
}
#endif /* folder_opt_h */
