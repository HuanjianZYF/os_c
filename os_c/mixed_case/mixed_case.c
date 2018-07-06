//
//  mixed_case.c
//  os_c
//
//  Created by mac_zyf on 2018/7/5.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "mixed_case.h"

int main() {
    struct passwd *pwd; //登录项
    struct group *grp; //组项
    struct utsname name; //系统相关信息
    time_t t; //时间
    struct tm *formattime; //带时分秒的时间
    
    //根据uid或者name，获取登录项
    pwd = getpwuid(0);
    printf("登录名：%s 密码：%s 启动shell：%s\n", pwd->pw_name, pwd->pw_passwd, pwd->pw_shell);
    pwd = getpwnam("zyf");
    printf("登录名：%s 密码：%s 启动shell：%s\n", pwd->pw_name, pwd->pw_passwd, pwd->pw_shell);
    
    //遍历登录项
    setpwent(); //重置登录项文件避免之前已经打开的情况
    while ((pwd = getpwent()) != NULL) {
        printf("登录名：%s 密码：%s 启动shell：%s\n", pwd->pw_name, pwd->pw_passwd, pwd->pw_shell);
    }
    endpwent(); //关闭登录项文件
    
    //根据gid得到组项
    grp = getgrgid(0);
    printf("gid：%d 组名：%s\n", grp->gr_gid, grp->gr_name);
    
    //遍历组项
    setgrent();
    while ((grp = getgrent()) != NULL) {
        grp = getgrent();
        printf("gid：%d 组名：%s\n", grp->gr_gid, grp->gr_name);
    }
    endgrent();
    
    //获取系统相关信息
    uname(&name);
    printf("操作系统名：%s 主机名：%s 发布：%s 版本：%s 硬件类型：%s\n", name.sysname, name.nodename, name.release, name.version, name.machine);
    
    //获取当前时间
    time(&t);
    formattime = localtime(&t);
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", formattime->tm_year + 1900, formattime->tm_mon + 1, formattime->tm_mday
           , formattime->tm_hour, formattime->tm_min, formattime->tm_sec);
}
